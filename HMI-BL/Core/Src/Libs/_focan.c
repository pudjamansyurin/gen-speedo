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
static uint8_t FOCAN_Response(uint16_t address, uint8_t payload);
static uint8_t FOCAN_xEnterModeIAP(void);
static uint8_t FOCAN_xGetVersion(uint16_t *version);

/* Public functions implementation --------------------------------------------*/
uint8_t FOCAN_Update(void) {
    uint32_t tick, tickIndicator;
    uint8_t p;
    uint16_t version = 0xABCD;

    /* Enter IAP Mode */
    p = FOCAN_xEnterModeIAP();

    // Wait command
    if (p) {
        tickIndicator = _GetTickMS();
        while (p) {
            //            // handle timeout
            //            if ((_GetTickMS() - tick) < 1000) {
            //                p = 0;
            //                break;
            //            }
            // read
            if (CB.fifo) {
                CB.fifo = 0;
                switch (CANBUS_ReadID()) {
                    case CAND_ENTER_IAP :
                        p = FOCAN_xEnterModeIAP();
                        break;
                    case CAND_GET_VERSION :
                        p = FOCAN_xGetVersion(&version);
                        break;
                    default:
                        break;
                }
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
static uint8_t FOCAN_Response(uint16_t address, uint8_t payload) {
    CAN_DATA *txd = &(CB.tx.data);

    // set message
    txd->u8[0] = payload;

    // send message
    return CANBUS_Write(address, 1, 0);
}

static uint8_t FOCAN_xEnterModeIAP(void) {
    return FOCAN_Response(CAND_ENTER_IAP, FOCAN_ACK);
}

static uint8_t FOCAN_xGetVersion(uint16_t *version) {
    CAN_DATA *txd = &(CB.tx.data);
    uint16_t address = CAND_GET_VERSION;
    uint8_t p;

    // ack
    p = FOCAN_Response(address, FOCAN_ACK);

    // version
    if (p) {
        // set message
        txd->u16[0] = *version;
        // send message
        p = CANBUS_Write(address, 2, 0);
    }

    // option message (2 bytes)
    if (p) {
        // set message
        txd->u16[0] = 0x0000;
        // send message
        p = CANBUS_Write(address, 2, 0);
    }

    // ack
    if (p) {
        p = FOCAN_Response(address, FOCAN_ACK);
    }

    return p;
}

