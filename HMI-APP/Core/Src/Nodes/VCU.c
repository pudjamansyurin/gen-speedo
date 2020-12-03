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

/* External variables ---------------------------------------------------------*/
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
void VCU_CAN_RX_SwitchModeControl(can_rx_t *Rx) {
  // read message
  HMI1.d.state.abs = _R1(Rx->data.u8[0], 0);
  HMI1.d.state.mirroring = _R1(Rx->data.u8[0], 1);
  HMI1.d.state.lamp = _R1(Rx->data.u8[0], 2);
  HMI1.d.state.warning = _R1(Rx->data.u8[0], 3);
  HMI1.d.state.overheat = _R1(Rx->data.u8[0], 4);
  HMI1.d.state.finger = _R1(Rx->data.u8[0], 5);
  HMI1.d.state.keyless = _R1(Rx->data.u8[0], 6);
  HMI1.d.state.daylight = _R1(Rx->data.u8[0], 7);

  // sein
  HMI1.d.sein.left = _R1(Rx->data.u8[1], 0);
  HMI1.d.sein.right = _R1(Rx->data.u8[1], 1);
  HMI1.d.mode.reverse = _R1(Rx->data.u8[1], 2);

  // mode
  HMI1.d.mode.val[SW_M_DRIVE] = _R2(Rx->data.u8[2], 0);
  HMI1.d.mode.val[SW_M_TRIP] = _R1(Rx->data.u8[2], 2);
  HMI1.d.mode.val[SW_M_REPORT] = _R1(Rx->data.u8[2], 4);
  HMI1.d.mode.sel = _R2(Rx->data.u8[2], 5);
  HMI1.d.mode.hide = _R1(Rx->data.u8[2], 7);

  // others
  VCU.d.speed = Rx->data.u8[3];

  // convert Speed to RPM
  MCU.d.rpm = VCU.d.speed * MCU_RPM_MAX / MCU_SPEED_MAX;
  //  MCU.d.temperature = ?
}

void VCU_CAN_RX_MixedData(can_rx_t *Rx) {
  // read message
  VCU.d.signal = Rx->data.u8[0];
  BMS.d.soc = Rx->data.u8[1];

  // decide report value according to mode
  if (HMI1.d.mode.val[SW_M_REPORT] == SW_M_REPORT_RANGE)
    HMI1.d.mode.report = Rx->data.u8[2];
  else
    HMI1.d.mode.report = Rx->data.u8[3];

  // odometer
  VCU.d.odometer = Rx->data.u32[1];
  if (HMI1.d.mode.val[SW_M_TRIP] == SW_M_TRIP_ODO)
    HMI1.d.mode.trip = VCU.d.odometer;
}

void VCU_CAN_RX_SubTripData(can_rx_t *Rx) {
  // read message
  if (HMI1.d.mode.val[SW_M_TRIP] == SW_M_TRIP_A)
    HMI1.d.mode.trip = Rx->data.u32[0];
  else if (HMI1.d.mode.val[SW_M_TRIP] == SW_M_TRIP_B)
    HMI1.d.mode.trip = Rx->data.u32[1];
}
