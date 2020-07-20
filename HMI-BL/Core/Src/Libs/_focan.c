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
#include "BSP/_lcd.h"

/* External variables ---------------------------------------------------------*/
extern canbus_t CB;

/* Private functions prototypes -----------------------------------------------*/
static uint8_t FOCAN_SendResponse(uint32_t address, FOCAN response);
static uint8_t FOCAN_SendSqueeze(uint32_t address, void *data, uint8_t size);

/* Public functions implementation --------------------------------------------*/
uint8_t FOCAN_Upgrade(uint8_t factory) {
    uint8_t p, related, success = 0;
    uint32_t timeout = 5000;
    uint32_t tick, iTick;
    uint32_t SIZE;
    IAP_TYPE type = IAP_HMI;

    /* Initialize LCD */
    BSP_LCD_Init();
    FOTA_DisplayPercent(0);

    // Wait command
    tick = _GetTickMS();
    iTick = tick;
    do {
        // read
        if (CANBUS_Read()) {
            related = 1;
            switch (CANBUS_ReadID()) {
                case CAND_ENTER_IAP :
                    p = FOCAN_xEnterModeIAP(&type);
                    /* Wait until network connected */
                    timeout = 90000;
                    break;
                case CAND_GET_CHECKSUM :
                    p = FOCAN_xGetChecksum();
                    break;
                case CAND_PRA_DOWNLOAD :
                    FOTA_DisplayStatus("Pra-Download.");
                    p = FOCAN_xPraDownload(&SIZE);
                    break;
                case CAND_INIT_DOWNLOAD :
                    p = FOCAN_xDownloadFlash(&SIZE, timeout, &tick);
                    break;
                case CAND_PASCA_DOWNLOAD :
                    FOTA_DisplayStatus("Pasca-Download");
                    p = FOCAN_xPascaDownload(&SIZE);
                    /* Handle success DFU */
                    success = p;
                    break;
                case CAND_SET_PROGRESS :
                    FOCAN_xSetProgress(&type);
                    break;
                case CAND_VCU_SWITCH :
                    /* VCU enter normal mode */
                    if (type == IAP_HMI) {
                        p = (factory ? FOCAN_RequestFota() : 0);
                    } else {
                        success = 1;
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
    } while (p && !success);

    // Final response
    if (type == IAP_HMI) {
        if (success) {
            FOTA_DisplayStatus("Success.");
        } else {
            FOTA_DisplayStatus("Failed.");
        }
        _DelayMS(1000);
    }

    return p;
}

uint8_t FOCAN_RequestFota(void) {
    CAN_DATA *txd = &(CB.tx.data);

    // Set message
    txd->u16[0] = 0xFFFF;
    // send message
    return CANBUS_Write(CAN_MY_ADRESS, 2);
}

uint8_t FOCAN_xEnterModeIAP(IAP_TYPE *type) {
    uint32_t address = CAND_ENTER_IAP;
    CAN_DATA *rxd = &(CB.rx.data);
    CAN_DATA txd;

    // Get IAP type
    *type = rxd->u32[0];

    // Handle FOTA
    FOTA_DisplayNode(type);

    // Set message
    txd.u32[0] = *type;
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

uint8_t FOCAN_xSetProgress(IAP_TYPE *type) {
    CAN_DATA *rxd = &(CB.rx.data);
    uint8_t p, percent;

    // Get
    *type = rxd->u32[0];
    percent = rxd->u8[4];

    // Handle
    FOTA_DisplayNode(type);
    FOTA_DisplayStatus(percent ? "Downloading..." : "Connecting...");
    FOTA_DisplayPercent(percent);

    // Send response
    p = 1;

    return p;
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
    uint32_t offset, currentSize, address;
    uint16_t pos = 0;
    uint8_t p, percent, len = 0, ptr[BLK_SIZE ];

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
        percent = offset * 100 / *size;
        LOG_Str("FOTA:Progress = ");
        LOG_Int(offset);
        LOG_Str(" Bytes (");
        LOG_Int(percent);
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
