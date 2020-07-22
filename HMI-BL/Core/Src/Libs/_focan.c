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

/* Private functions prototypes -----------------------------------------------*/
static uint8_t FOCAN_SendResponse(uint32_t address, FOCAN response);
static uint8_t FOCAN_SendSqueeze(uint32_t address, void *data, uint8_t size);

/* Public functions implementation --------------------------------------------*/
uint8_t FOCAN_Upgrade(uint8_t factory) {
    can_rx_t Rx;
    uint8_t p, success = 0;
    uint32_t timeout = 10000;
    uint32_t tick, iTick;
    uint32_t SIZE;
    IAP_TYPE type = IAP_HMI;

    // Empty Firmware
    if (factory) {
        FOTA_DisplayDevice(IAP_HMI);
        FOTA_DisplayStatus("No Firmware.");
        FOCAN_RequestFota();
    }
    FOTA_DisplayPercent(0);

    // Wait command
    tick = _GetTickMS();
    iTick = tick;
    do {
        // read
        if (CANBUS_Read(&Rx)) {
            switch (CANBUS_ReadID(&(Rx.header))) {
                case CAND_GET_CHECKSUM :
                    tick = _GetTickMS();
                    p = FOCAN_xGetChecksum();
                    break;
                case CAND_PRA_DOWNLOAD :
                    tick = _GetTickMS();
                    FOTA_DisplayStatus("Pra-Download.");
                    p = FOCAN_xPraDownload(&Rx, &SIZE);
                    break;
                case CAND_INIT_DOWNLOAD :
                    tick = _GetTickMS();
                    p = FOCAN_xDownloadFlash(&Rx, &SIZE, timeout, &tick);
                    break;
                case CAND_PASCA_DOWNLOAD :
                    tick = _GetTickMS();
                    FOTA_DisplayStatus("Pasca-Download");
                    p = FOCAN_xPascaDownload(&Rx, &SIZE);
                    /* Handle success DFU */
                    success = p;
                    break;
                case CAND_SET_PROGRESS :
                    tick = _GetTickMS();
                    FOCAN_xSetProgress(&Rx, &type);
                    break;
                case CAND_VCU_SWITCH :
                    if (factory) {
                        FOCAN_RequestFota();
                    }
//                    /* VCU enter normal mode */
//                    if (type == IAP_HMI) {
//                        p = (factory ? FOCAN_RequestFota() : 0);
//                    } else {
//                        success = 1;
//                    }
                    break;
                default:
                    break;
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
    CAN_DATA TxData;

    // Set message
    TxData.u16[0] = 0xFFFF;
    // send message
    return CANBUS_Write(CAND_HMI1, &TxData, 2);
}

uint8_t FOCAN_xGetChecksum(void) {
    uint32_t address = CAND_GET_CHECKSUM;
    uint32_t checksum;

    // Make message
    FOTA_GetChecksum(&checksum);

    // Send response
    return FOCAN_SendSqueeze(address, &checksum, 4);
}

uint8_t FOCAN_xSetProgress(can_rx_t *Rx, IAP_TYPE *type) {
    uint8_t p, percent;

    // Get
    *type = Rx->data.u32[0];
    percent = Rx->data.u8[4];

    // Handle
    FOTA_DisplayDevice(*type);
    FOTA_DisplayStatus(percent ? "Downloading..." : "Connecting...");
    FOTA_DisplayPercent(percent);

    // Send response
    p = 1;

    return p;
}

uint8_t FOCAN_xPraDownload(can_rx_t *Rx, uint32_t *size) {
    uint32_t address = CAND_PRA_DOWNLOAD;
    uint8_t p;

    // Read
    *size = Rx->data.u32[0];

    // Execute
    p = FLASHER_BackupApp();

    // Send response
    FOCAN_SendResponse(address, p ? FOCAN_ACK : FOCAN_NACK);

    return p;
}

uint8_t FOCAN_xDownloadFlash(can_rx_t *Rx, uint32_t *size, uint32_t timeout, uint32_t *tick) {
    uint32_t offset, currentSize, address;
    uint8_t p, percent, len = 0, ptr[BLK_SIZE ];
    uint16_t pos = 0;

    // read
    offset = Rx->data.u32[0];
    currentSize = Rx->data.u16[2] + 1;

    // check the flash size
    p = (offset + currentSize) <= APP_MAX_SIZE;
    // Send response
    FOCAN_SendResponse(CAND_INIT_DOWNLOAD, p ? FOCAN_ACK : FOCAN_NACK);

    // Wait data
    if (p) {
        *tick = _GetTickMS();
        do {
            // read
            if (CANBUS_Read(Rx)) {
                if (_R(CANBUS_ReadID(&(Rx->header)), 20) == CAND_DOWNLOADING) {
                    pos = (CANBUS_ReadID(&(Rx->header)) & 0xFFFF);

                    // read
                    len = Rx->header.DLC;
                    memcpy(&ptr[pos], &(Rx->data), len);

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

uint8_t FOCAN_xPascaDownload(can_rx_t *Rx, uint32_t *size) {
    uint32_t address = CAND_PASCA_DOWNLOAD;
    uint32_t checksum;
    uint8_t p;

    // Read
    checksum = Rx->data.u32[0];

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
    CAN_DATA TxData;
    uint8_t retry = FOCAN_RETRY, p;

    do {
        // ack
        p = FOCAN_SendResponse(address, FOCAN_ACK);
        // version
        if (p) {
            // set message
            memcpy(&TxData, data, size);
            // send message
            p = CANBUS_Write(address, &TxData, size);
        }
        // ack
        if (p) {
            p = FOCAN_SendResponse(address, FOCAN_ACK);
        }
    } while (!p && --retry);

    return p;
}

static uint8_t FOCAN_SendResponse(uint32_t address, FOCAN response) {
    CAN_DATA TxData;
    uint8_t retry = FOCAN_RETRY, p;

    do {
        // set message
        TxData.u8[0] = response;
        // send message
        p = CANBUS_Write(address, &TxData, 1);
    } while (!p && --retry);

    return p;
}
