/*
 * _focan.c
 *
 *  Created on: 29 Jun 2020
 *      Author: geni
 */

/* Includes ------------------------------------------------------------------*/
#include "Libs/_focan.h"
#include "Drivers/_flasher.h"
#include "Drivers/_canbus.h"

/* External variables ---------------------------------------------------------*/
extern canbus_t CB;

/* Private functions prototypes -----------------------------------------------*/
static uint8_t FOCAN_Response(uint32_t address, FOCAN response);
static uint8_t FOCAN_Squeeze(uint32_t address, void *data, uint8_t size);

/* Public functions implementation --------------------------------------------*/
uint8_t FOCAN_Update(void) {
    uint32_t tick, iTick, timeout = 5000;
    uint32_t SIZE, CHECKSUM = 0x89ABCDEF;
    uint8_t p, related;

    /* Enter IAP Mode */
    p = FOCAN_xEnterModeIAP();

    // Wait command
    if (p) {
        tick = _GetTickMS();
        iTick = tick;
        while (p) {
            // read
            if (CANBUS_Read()) {
                related = 1;
                switch (CANBUS_ReadID()) {
                    case CAND_ENTER_IAP :
                        p = FOCAN_xEnterModeIAP();
                        break;
                    case CAND_GET_CHECKSUM :
                        p = FOCAN_xGetChecksum(&CHECKSUM);
                        break;
                    case CAND_PRA_DOWNLOAD :
                        p = FOCAN_xPraDownload(&SIZE);
                        break;
                    case CAND_PASCA_DOWNLOAD :
                        p = FOCAN_xPascaDownload(&SIZE);
                        break;
                    case CAND_INIT_DOWNLOAD :
                        p = FOCAN_xDownloadFlash(1000);
                        break;

                    default:
                        related = 0;
                        break;
                }

                // update tick on each related commands
                if (related) {
                    tick = _GetTickMS();
                }
            }

            // indicator
            if ((_GetTickMS() - iTick) > 100) {
                iTick = _GetTickMS();
                _LedToggle();
            }

            // handle timeout
            if ((_GetTickMS() - tick) > timeout) {
                p = 0;
                break;
            }
        }
    }

    return p;
}

uint8_t FOCAN_xEnterModeIAP(void) {
    uint32_t address = CAND_ENTER_IAP;
    CAN_DATA txd;

    // Set message
    txd.u32[0] = CAN_MY_ADRESS;

    // Send response
    return FOCAN_Squeeze(address, &txd, 4);
}

uint8_t FOCAN_xGetChecksum(uint32_t *checksum) {
    uint32_t address = CAND_GET_CHECKSUM;

    // Send response
    return FOCAN_Squeeze(address, checksum, 4);
}

uint8_t FOCAN_xPraDownload(uint32_t *size) {
    uint32_t address = CAND_PRA_DOWNLOAD;
    CAN_DATA *rxd = &(CB.rx.data);
    uint8_t p;

    // Read
    *size = rxd->u32[0];

    // Execute
    p = FLASHER_BackupApp();

    // Send response
    if (p) {
        p = FOCAN_Response(address, FOCAN_ACK);
    } else {
        FOCAN_Response(address, FOCAN_NACK);
    }

    return p;
}

uint8_t FOCAN_xPascaDownload(uint32_t *size) {
    uint32_t address = CAND_PASCA_DOWNLOAD;
    CAN_DATA *rxd = &(CB.rx.data);
    uint32_t checksum;
    uint8_t p;

    // Read
    checksum = rxd->u32[0];

    // Execute
    p = FOTA_ValidateChecksum(checksum, *size, APP_START_ADDR);
    // Glue related information to new image
    if (p) {
        FOTA_GlueInfo32(CHECKSUM_OFFSET, &checksum);
        FOTA_GlueInfo32(SIZE_OFFSET, size);
    }

    // Send response
    if (p) {
        p = FOCAN_Response(address, FOCAN_ACK);
    } else {
        FOCAN_Response(address, FOCAN_NACK);
    }

    return p;
}

uint8_t FOCAN_xDownloadFlash(uint32_t timeout) {
    CAN_RxHeaderTypeDef *rxh = &(CB.rx.header);
    CAN_DATA *rxd = &(CB.rx.data);
    uint8_t ptr[BLK_SIZE];
    uint32_t offset, size;
    uint32_t tick;
    uint8_t pos = 0;
    uint8_t p;

    // read
    offset = rxd->u32[0];
    size = rxd->u8[5];

    // check the buffer size
    p = size <= BLK_SIZE;
    // check the flash size
    if (p) {
        p = (offset + size) <= APP_MAX_SIZE;
    }
    // Send response
    if (p) {
        p = FOCAN_Response(CAND_INIT_DOWNLOAD, FOCAN_ACK);
    } else {
        FOCAN_Response(CAND_INIT_DOWNLOAD, FOCAN_NACK);
    }

    // Wait data
    if (p) {
        tick = _GetTickMS();
        while (p && pos < size) {
            // read
            if (CANBUS_Read()) {
                if (CANBUS_ReadID() == CAND_DOWNLOADING) {
                    // read
                    memcpy(&ptr[pos], rxd, rxh->DLC);

                    // update pointer
                    pos += rxh->DLC;

                    // update tick
                    tick = _GetTickMS();
                    _LedToggle();

                    // response ACK
                    FOCAN_Response(CAND_DOWNLOADING, FOCAN_ACK);
                }
            }

            // handle timeout
            if ((_GetTickMS() - tick) > timeout) {
                p = 0;
                break;
            }
        }
    }

    // flash to firmware
    if (p) {
        p = FLASHER_WriteAppArea(ptr, size, offset);
    }

    // send final response
    if (p) {
        p = FOCAN_Response(CAND_INIT_DOWNLOAD, FOCAN_ACK);
    } else {
        FOCAN_Response(CAND_INIT_DOWNLOAD, FOCAN_NACK);
    }

    return p;
}

/* Private functions implementation ------------------------------------------*/
static uint8_t FOCAN_Response(uint32_t address, FOCAN response) {
    CAN_DATA *txd = &(CB.tx.data);

    // set message
    txd->u8[0] = response;

    // send message
    return CANBUS_Write(address, 1);
}

static uint8_t FOCAN_Squeeze(uint32_t address, void *data, uint8_t size) {
    CAN_DATA *txd = &(CB.tx.data);
    uint8_t p;

    // ack
    p = FOCAN_Response(address, FOCAN_ACK);
    // version
    if (p) {
        // set message
        memcpy(txd, data, size);
        // send message
        p = CANBUS_Write(address, size);
    }
    // ack
    if (p) {
        p = FOCAN_Response(address, FOCAN_ACK);
    }

    return p;
}
