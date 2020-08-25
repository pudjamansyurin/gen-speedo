/*
 * HMI1.c
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

/* Includes ------------------------------------------------------------------*/
#include "Nodes/HMI1.h"
#include "Drivers/_canbus.h"

/* Public variables -----------------------------------------------------------*/
hmi1_t HMI1 = {
        .d = {
                .status = { 0 },
                .mode = { 0 },
        },
        .can = {
                .t = {
                        HMI1_CAN_TX_Heartbeat
                }
        },
        HMI1_Init
};

/* Public functions implementation --------------------------------------------*/
void HMI1_Init(void) {
    HMI1.d.status.abs = 0;
    HMI1.d.status.mirroring = 0;
    HMI1.d.status.lamp = 0;
    HMI1.d.status.warning = 1;
    HMI1.d.status.overheat = 0;
    HMI1.d.status.finger = 0;
    HMI1.d.status.keyless = 0;
    HMI1.d.status.daylight = 1;

    HMI1.d.sein.left = 0;
    HMI1.d.sein.right = 0;

    HMI1.d.mode.reverse = 0;
    HMI1.d.mode.sel = SW_M_TRIP;
    HMI1.d.mode.hide = 0;
    HMI1.d.mode.val[SW_M_DRIVE] = SW_M_DRIVE_ECONOMY;
    HMI1.d.mode.val[SW_M_TRIP] = SW_M_TRIP_ODO;
    HMI1.d.mode.val[SW_M_REPORT] = SW_M_REPORT_RANGE;
    HMI1.d.mode.trip = 0;
    HMI1.d.mode.report = 0;
}

/* ====================================== CAN TX =================================== */
uint8_t HMI1_CAN_TX_Heartbeat(void) {
    CAN_DATA TxData;

    // set message
    TxData.u16[0] = HMI_VERSION;
    // send message
    return CANBUS_Write(CAND_HMI1, &TxData, 2);
}
