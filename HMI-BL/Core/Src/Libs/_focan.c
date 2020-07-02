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
    uint32_t tick, iTick, timeout = 10000;
    uint32_t checksum = 0x89ABCDEF;
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
                        p = FOCAN_xGetChecksum(&checksum);
                        timeout = 60000;
                        break;
                    default:
                        related = 0;
                        break;
                }

                // update tick on each related commands
                if (related) {
                    tick = _GetTickMS();
                    _LedToggle();
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

/* Private functions implementation ------------------------------------------*/
static uint8_t FOCAN_Response(uint32_t address, FOCAN response) {
    CAN_DATA *txd = &(CB.tx.data);

    // set message
    txd->u8[0] = response;

    // send message
    return CANBUS_Write(address, 1);
}

static uint8_t FOCAN_xEnterModeIAP(void) {
    CAN_DATA *txd = &(CB.tx.data);
    uint32_t address = CAND_ENTER_IAP;
    uint8_t p;

    // ack
    p = FOCAN_Response(address, FOCAN_ACK);
    // version
    if (p) {
        // set message
        txd->u32[0] = CAN_MY_ADRESS;
        // send message
        p = CANBUS_Write(address, 4);
    }
    // ack
    if (p) {
        p = FOCAN_Response(address, FOCAN_ACK);
    }

    return p;
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

