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
static uint8_t FOCAN_SendResponse(uint32_t address, FOCAN response);
static uint8_t FOCAN_SendSqueeze(uint32_t address, void *data, uint8_t size);

/* Public functions implementation --------------------------------------------*/
uint8_t FOCAN_Upgrade(uint8_t update) {
    uint32_t timeout = 5000;
    uint32_t tick, iTick;
    uint8_t p, related;
    uint32_t SIZE;

    /* Enter IAP Mode */
    FOCAN_xEnterModeIAP();

    // Wait command
    tick = _GetTickMS();
    iTick = tick;
    do {
        // read
        if (CANBUS_Read()) {
            related = 1;
            switch (CANBUS_ReadID()) {
                case CAND_ENTER_IAP :
                    p = FOCAN_xEnterModeIAP();
                    break;
                case CAND_GET_CHECKSUM :
                    p = FOCAN_xGetChecksum();
                    /* Wait until network connected */
                    timeout = 60000;
                    break;
                case CAND_PRA_DOWNLOAD :
                    p = FOCAN_xPraDownload(&SIZE);
                    break;
                case CAND_INIT_DOWNLOAD :
                    p = FOCAN_xDownloadFlash(&SIZE, timeout, &tick);
                    break;
                case CAND_PASCA_DOWNLOAD :
                    p = FOCAN_xPascaDownload(&SIZE);
                    /* Handle success DFU */
                    if (p) {
                        FOTA_Reboot();
                    }
                    break;
                case CAND_VCU_SWITCH :
                    /* VCU enter normal mode */
                    if (!update) {
                        p = FOCAN_RequestFota();
                    } else {
                        p = 0;
                    }
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
        if (_GetTickMS() - tick > timeout) {
            p = 0;
        }
    } while (p);

    return p;
}

uint8_t FOCAN_RequestFota(void) {
    CAN_DATA *txd = &(CB.tx.data);

    // Set message
    txd->u16[0] = 0xFFFF;
    // send message
    return CANBUS_Write(CAN_MY_ADRESS, 2);
}

uint8_t FOCAN_xEnterModeIAP(void) {
    uint32_t address = CAND_ENTER_IAP;
    CAN_DATA txd;

    // Set message
    txd.u32[0] = CAN_MY_ADRESS;

    // Send response
    return FOCAN_SendSqueeze(address, &txd, 4);
}

uint8_t FOCAN_xGetChecksum(void) {
    uint32_t address = CAND_GET_CHECKSUM;
    uint32_t checksum;

    // Make message
    FOTA_GetChecksum(&checksum);

    // Send response
    return FOCAN_SendSqueeze(address, &checksum, 4);
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
    FOCAN_SendResponse(address, p ? FOCAN_ACK : FOCAN_NACK);

    return p;
}

uint8_t FOCAN_xDownloadFlash(uint32_t *size, uint32_t timeout, uint32_t *tick) {
    CAN_RxHeaderTypeDef *rxh = &(CB.rx.header);
    CAN_DATA *rxd = &(CB.rx.data);
    uint32_t offset, currentSize;
    uint8_t ptr[BLK_SIZE ];
    uint32_t address;
    uint16_t pos = 0;
    uint8_t p, len = 0;

    // read
    offset = rxd->u32[0];
    currentSize = rxd->u16[2] + 1;

    // check the flash size
    p = (offset + currentSize) <= APP_MAX_SIZE;
    // Send response
    FOCAN_SendResponse(CAND_INIT_DOWNLOAD, p ? FOCAN_ACK : FOCAN_NACK);

    // Wait data
    if (p) {
        *tick = _GetTickMS();
        do {
            // read
            if (CANBUS_Read()) {
                if (_R(CANBUS_ReadID(), 20) == CAND_DOWNLOADING) {
                    pos = (CANBUS_ReadID() & 0xFFFF);

                    // read
                    len = rxh->DLC;
                    memcpy(&ptr[pos], rxd, len);

                    // response ACK
                    address = _L(CAND_DOWNLOADING, 20) | pos;
                    p = FOCAN_SendResponse(address, FOCAN_ACK);

                    // update tick
                    *tick = _GetTickMS();
                    _LedToggle();
                }
            }
            // handle timeout
            if ((_GetTickMS() - *tick > timeout)) {
                p = 0;
            }
        } while (p && ((pos + len) < currentSize));
    }

    // validate received size
    if (p) {
        p = ((pos + len) == currentSize);
    }

    // flash to firmware
    if (p) {
        p = FLASHER_WriteAppArea(ptr, currentSize, offset);
    }

    // progress indicator
    if (p) {
        LOG_Str("FOTA:Progress = ");
        LOG_Int(offset);
        LOG_Str(" Bytes (");
        LOG_Int(offset * 100 / *size);
        LOG_StrLn("%)");
    }

    // send final response
    FOCAN_SendResponse(CAND_INIT_DOWNLOAD, p ? FOCAN_ACK : FOCAN_NACK);

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
    FOCAN_SendResponse(address, p ? FOCAN_ACK : FOCAN_NACK);

    return p;
}

/* Private functions implementation ------------------------------------------*/
static uint8_t FOCAN_SendSqueeze(uint32_t address, void *data, uint8_t size) {
    CAN_DATA *txd = &(CB.tx.data);
    uint8_t retry = FOCAN_RETRY, p;

    do {
        // ack
        p = FOCAN_SendResponse(address, FOCAN_ACK);
        // version
        if (p) {
            // set message
            memcpy(txd, data, size);
            // send message
            p = CANBUS_Write(address, size);
        }
        // ack
        if (p) {
            p = FOCAN_SendResponse(address, FOCAN_ACK);
        }
    } while (!p && --retry);

    return p;
}

static uint8_t FOCAN_SendResponse(uint32_t address, FOCAN response) {
    CAN_DATA *txd = &(CB.tx.data);
    uint8_t retry = FOCAN_RETRY, p;

    do {
        // set message
        txd->u8[0] = response;
        // send message
        p = CANBUS_Write(address, 1);
    } while (!p && --retry);

    return p;
}
