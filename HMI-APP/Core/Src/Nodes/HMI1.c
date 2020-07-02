/*
 * HMI1.c
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

/* Includes ------------------------------------------------------------------*/
#include "Nodes/HMI1.h"
#include "Drivers/_canbus.h"

/* External variables ---------------------------------------------------------*/
extern canbus_t CB;

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
    HMI1.d.status.mirror = 0;
    HMI1.d.status.lamp = 0;
    HMI1.d.status.warning = 1;
    HMI1.d.status.overheat = 0;
    HMI1.d.status.finger = 0;
    HMI1.d.status.keyless = 0;
    HMI1.d.status.daylight = 1;
    HMI1.d.status.sein_left = 0;
    HMI1.d.status.sein_right = 0;

    HMI1.d.mode.sel = SW_M_TRIP;
    HMI1.d.mode.hide = 0;
    HMI1.d.mode.drive = SW_M_DRIVE_E;
    HMI1.d.mode.trip.sel = SW_M_TRIP_A;
    HMI1.d.mode.trip.val = 0;
    HMI1.d.mode.report.sel = SW_M_REPORT_RANGE;
    HMI1.d.mode.report.val = 0;
}

/* ====================================== CAN TX =================================== */
uint8_t HMI1_CAN_TX_Heartbeat(void) {
    // send message
    return CANBUS_Write(CAN_MY_ADRESS, 0);
}
