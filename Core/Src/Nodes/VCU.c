/*
 * VCU.c
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

/* Includes ------------------------------------------------------------------*/
#include "Nodes/VCU.h"
#include "Nodes/HMI1.h"
#include "Nodes/BMS.h"
#include "Nodes/MCU.h"
#include "Drivers/_canbus.h"

/* External variables ---------------------------------------------------------*/
extern canbus_t CB;
extern hmi1_t HMI1;
extern bms_t BMS;
extern mcu_t MCU;

/* Public variables -----------------------------------------------------------*/
vcu_t VCU = {
        .d = { 0 },
        .can = {
                .r = {
                        VCU_CAN_RX_SwitchModeControl,
                        VCU_CAN_RX_MixedData,
                        VCU_CAN_RX_SubTripData
                }
        },
        VCU_Init
};

/* Public functions implementation --------------------------------------------*/
void VCU_Init(void) {
    VCU.d.signal = 0;
    VCU.d.speed = 0;
    VCU.d.odometer = 0;
}

/* ====================================== CAN RX =================================== */
void VCU_CAN_RX_SwitchModeControl(void) {
    CAN_DATA *data = &(CB.rx.data);

    // read message
    HMI1.d.status.abs = _R1(data->u8[0], 0);
    HMI1.d.status.mirror = _R1(data->u8[0], 1);
    HMI1.d.status.lamp = _R1(data->u8[0], 2);
    HMI1.d.status.warning = _R1(data->u8[0], 3);
    HMI1.d.status.overheat = _R1(data->u8[0], 4);
    HMI1.d.status.finger = _R1(data->u8[0], 5);
    HMI1.d.status.keyless = _R1(data->u8[0], 6);
    HMI1.d.status.daylight = _R1(data->u8[0], 7);

    // sein
    HMI1.d.status.sein_left = _R1(data->u8[1], 0);
    HMI1.d.status.sein_right = _R1(data->u8[1], 1);

    // mode
    HMI1.d.mode.drive = _R2(data->u8[2], 0);
    HMI1.d.mode.trip.sel = _R1(data->u8[2], 2);
    HMI1.d.mode.report.sel = _R1(data->u8[2], 3);
    HMI1.d.mode.sel = _R2(data->u8[2], 4);
    HMI1.d.mode.hide = _R1(data->u8[2], 6);

    // others
    VCU.d.speed = data->u8[3];

    // FIXME: use real value
    // convert Speed to RPM
    MCU.d.rpm = VCU.d.speed * MCU_RPM_MAX / MCU_SPEED_MAX;
    //  MCU.d.temperature = ?

    // update backlight state
    _SetBacklight(HMI1.d.status.daylight);
}

void VCU_CAN_RX_MixedData(void) {
    CAN_DATA *data = &(CB.rx.data);

    // read message
    VCU.d.signal = data->u8[0];
    BMS.d.soc = data->u8[1];

    // decide report value according to mode
    if (HMI1.d.mode.report.sel == SW_M_REPORT_RANGE) {
        HMI1.d.mode.report.val = data->u8[2];
    } else {
        HMI1.d.mode.report.val = data->u8[3];
    }

    // odometer
    VCU.d.odometer = data->u32[1];
}

void VCU_CAN_RX_SubTripData(void) {
    CAN_DATA *data = &(CB.rx.data);

    // read message
    if (HMI1.d.mode.trip.sel == SW_M_TRIP_A) {
        HMI1.d.mode.trip.val = data->u32[0];
    } else {
        HMI1.d.mode.trip.val = data->u32[1];
    }
}
