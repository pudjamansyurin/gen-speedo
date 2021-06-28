/*
 * HMI1.c
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

/* Includes
 * --------------------------------------------*/
#include "Nodes/HMI1.h"

#include "Drivers/_canbus.h"
#include "Nodes/VCU.h"

/* Public variables
 * --------------------------------------------*/
hmi1_t HMI1 = {
    .hbar = {0},
    .d =
        {
            .state = {0},
            .sein = {0},
        },
};

/* Public functions implementation
 * --------------------------------------------*/
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

  HMI1.hbar.d.trip = 0;
  HMI1.hbar.d.prediction = 0;
  HMI1.hbar.reverse = 0;
  HMI1.hbar.listening = 0;
  HMI1.hbar.m = HBAR_M_DRIVE;
  HMI1.hbar.d.mode[HBAR_M_TRIP] = HBAR_M_TRIP_ODO;
  HMI1.hbar.d.mode[HBAR_M_DRIVE] = HBAR_M_DRIVE_STANDARD;
  HMI1.hbar.d.mode[HBAR_M_PREDICTION] = HBAR_M_PREDICTION_RANGE;
}

/* CAN TX
 * --------------------------------------------*/
uint8_t HMI1_TX_Heartbeat(void) {
  can_tx_t Tx = {0};
  UNION64 *d = &(Tx.data);

  d->u16[0] = HMI_VERSION;

  return CANBUS_Write(&Tx, CAND_HMI1, 2, 0);
}
