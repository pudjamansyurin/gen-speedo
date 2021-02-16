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
        .state = { 0 },
        .hbar = { 0 },
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
  HMI1.d.state.abs = 0;
  HMI1.d.state.mirroring = 0;
  HMI1.d.state.lamp = 0;
  HMI1.d.state.warning = 1;
  HMI1.d.state.overheat = 0;
  HMI1.d.state.unfinger = 1;
  HMI1.d.state.unremote = 1;
  HMI1.d.state.daylight = 1;

  HMI1.d.sein.left = 0;
  HMI1.d.sein.right = 0;

  HMI1.d.hbar.reverse = 0;
  HMI1.d.hbar.hide = 0;
  HMI1.d.hbar.sel = HBAR_M_DRIVE;
  HMI1.d.hbar.mode[HBAR_M_TRIP] = HBAR_M_TRIP_ODO;
  HMI1.d.hbar.mode[HBAR_M_DRIVE] = HBAR_M_DRIVE_STANDARD;
  HMI1.d.hbar.mode[HBAR_M_REPORT] = HBAR_M_REPORT_RANGE;
  HMI1.d.hbar.trip = 0;
  HMI1.d.hbar.report = 0;
}

/* ====================================== CAN TX =================================== */
uint8_t HMI1_CAN_TX_Heartbeat(void) {
  CAN_DATA TxData;

  // set message
  TxData.u16[0] = HMI_VERSION;
  // send message
  return CANBUS_Write(CAND_HMI1, &TxData, 2);
}
