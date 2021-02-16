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
            VCU_CAN_RX_TripData
        }
    },
    VCU_Init
};

/* Public functions implementation --------------------------------------------*/
void VCU_Init(void) {
  VCU.d.signal = 0;
  VCU.d.speed = 0;
}

/* ====================================== CAN RX =================================== */
void VCU_CAN_RX_SwitchModeControl(can_rx_t *Rx) {
  // read message
  HMI1.d.state.abs = (Rx->data.u8[0] >> 0) & 0x01;
  HMI1.d.state.mirroring = (Rx->data.u8[0] >> 1) & 0x01;
  HMI1.d.state.lamp = (Rx->data.u8[0] >> 2) & 0x01;
  HMI1.d.state.warning = (Rx->data.u8[0] >> 3) & 0x01;
  HMI1.d.state.overheat = (Rx->data.u8[0] >> 4) & 0x01;
  HMI1.d.state.unfinger = (Rx->data.u8[0] >> 5) & 0x01;
  HMI1.d.state.unremote = (Rx->data.u8[0] >> 6) & 0x01;
  HMI1.d.state.daylight = (Rx->data.u8[0] >> 7) & 0x01;

  // sein
  HMI1.d.sein.left = (Rx->data.u8[1] >> 0) & 0x01;
  HMI1.d.sein.right = (Rx->data.u8[1] >> 1) & 0x01;
  HMI1.hbar.reverse = (Rx->data.u8[1] >> 2) & 0x01;

  // mode
  HMI1.hbar.d.mode[HBAR_M_DRIVE] = (Rx->data.u8[2] >> 0) & 0x03;
  HMI1.hbar.d.mode[HBAR_M_TRIP] = (Rx->data.u8[2] >> 2) & 0x03;
  HMI1.hbar.d.mode[HBAR_M_REPORT] = (Rx->data.u8[2] >> 4) & 0x01;
  HMI1.hbar.m = (Rx->data.u8[2] >> 5) & 0x03;
  HMI1.hbar.hide = (Rx->data.u8[2] >> 7) & 0x01;

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
  if (HMI1.hbar.d.mode[HBAR_M_REPORT] == HBAR_M_REPORT_RANGE)
    HMI1.hbar.d.report = Rx->data.u8[2];
  else
    HMI1.hbar.d.report = Rx->data.u8[3];

}

void VCU_CAN_RX_TripData(can_rx_t *Rx) {
  // sub trip
  if (HMI1.hbar.d.mode[HBAR_M_TRIP] == HBAR_M_TRIP_A)
    HMI1.hbar.d.trip = Rx->data.u16[0];
  else if (HMI1.hbar.d.mode[HBAR_M_TRIP] == HBAR_M_TRIP_B)
    HMI1.hbar.d.trip = Rx->data.u16[1];
  else if (HMI1.hbar.d.mode[HBAR_M_TRIP] == HBAR_M_TRIP_ODO)
    HMI1.hbar.d.trip = Rx->data.u32[1];
}
