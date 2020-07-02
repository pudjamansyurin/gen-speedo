/*
 * _focan.c
 *
 *  Created on: 29 Jun 2020
 *      Author: geni
 */

/* Includes ------------------------------------------------------------------*/
#include "Libs/_focan.h"
#include "Drivers/_canbus.h"

/* External variables ---------------------------------------------------------*/
extern canbus_t CB;

/* Private functions prototypes -----------------------------------------------*/
static uint8_t FOCAN_Response(uint32_t address, FOCAN response);
static uint8_t FOCAN_xEnterModeIAP(void);
static uint8_t FOCAN_xGetChecksum(uint32_t *checksum);

/* Public functions implementation --------------------------------------------*/
uint8_t FOCAN_Update(void) {
    uint32_t tick, tickIndicator, timeout = 10000;
    uint32_t checksum = 0x89ABCDEF;
    uint8_t p;

    /* Enter IAP Mode */
    p = FOCAN_xEnterModeIAP();

    // Wait command
    if (p) {
        tick = _GetTickMS();
        tickIndicator = tick;
        while (p) {
            // read
            if (CANBUS_Read()) {
                switch (CANBUS_ReadID()) {
                    case CAND_ENTER_IAP :
                        p = FOCAN_xEnterModeIAP();
                        break;
                    case CAND_GET_CHECKSUM :
                        p = FOCAN_xGetChecksum(&checksum);
                        break;
                    default:
                        break;
                }
            }

            // handle timeout
            if ((_GetTickMS() - tick) > timeout) {
                p = 0;
                break;
            }

            // indicator
            if ((_GetTickMS() - tickIndicator) > 100) {
                tickIndicator = _GetTickMS();
                _LedToggle();
            }
        }
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

static uint8_t FOCAN_xEnterModeIAP(void) {
    return FOCAN_Response(CAND_ENTER_IAP, FOCAN_ACK);
}

static uint8_t FOCAN_xGetChecksum(uint32_t *checksum) {
    CAN_DATA *txd = &(CB.tx.data);
    uint32_t address = CAND_GET_CHECKSUM;
    uint8_t p;

    // ack
    p = FOCAN_Response(address, FOCAN_ACK);
    // version
    if (p) {
        // set message
        txd->u32[0] = *checksum;
        // send message
        p = CANBUS_Write(address, 4);
    }
    // ack
    if (p) {
        p = FOCAN_Response(address, FOCAN_ACK);
    }

    return p;
}

