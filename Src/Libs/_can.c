/**
 *  \file _canbus.c
 *	\brief CAN bridge
 *	\details This file handle abstraction layer beetween application and can.c file
 *  \date Oct 11, 2019
 *  \author Puja
 */
/* Includes ------------------------------------------------------------------*/
#include "_can.h"

/* External variables ------------------------------------------------------------------*/
extern canbus_t CB;
extern db_t DB;

// ==================================== HMI =========================================
#if (CAN_NODE & CAN_NODE_HMI)
uint8_t CAN_HMI_Heartbeat(void) {
  // set default header
  CANBUS_Header(&(CB.tx.header), CAN_ADDR_HMI_DUMMY + (USE_HMI_LEFT ? 1 : 0), 1);
  CB.tx.header.RTR = CAN_RTR_REMOTE;

  // send message
  return CANBUS_Write(&(CB.tx));
}

/* ------------------------------------ READER ------------------------------------- */
void CAN_VCU_Switch_Read(void) {
  // read message
  DB.hmi1.status.abs = CB.rx.data[0] & 0x01;
  DB.hmi1.status.mirror = BBR(CB.rx.data[0], 1);
  DB.hmi1.status.lamp = BBR(CB.rx.data[0], 2);
  DB.hmi1.status.warning = BBR(CB.rx.data[0], 3);
  DB.hmi1.status.temperature = BBR(CB.rx.data[0], 4);
  DB.hmi1.status.finger = BBR(CB.rx.data[0], 5);
  DB.hmi1.status.keyless = BBR(CB.rx.data[0], 6);
  DB.hmi1.status.daylight = BBR(CB.rx.data[0], 7);

  // sein
  DB.hmi1.status.sein_left = CB.rx.data[1] & 0x01;
  DB.hmi1.status.sein_right = BBR(CB.rx.data[1], 1);

  // signal
  DB.vcu.signal = CB.rx.data[2];

  // odometer
  DB.vcu.odometer = BSL(CB.rx.data[7], 24) | BSL(CB.rx.data[6], 16) | BSL(CB.rx.data[5], 8) | CB.rx.data[4];
}

void CAN_VCU_Select_Set_Read(void) {
  // read message
  DB.hmi1.mode.drive = CB.rx.data[0] & 0x03;
  DB.hmi1.mode.trip.sel = BBR(CB.rx.data[0], 2);
  DB.hmi1.mode.report.sel = BBR(CB.rx.data[0], 3);
  DB.hmi1.mode.sel = (CB.rx.data[0] >> 4) & 0x03;
  DB.hmi1.mode.hide = BBR(CB.rx.data[0], 6);

  // decide report value according to mode
  if (DB.hmi1.mode.report.sel == SW_M_REPORT_RANGE) {
    DB.hmi1.mode.report.val = CB.rx.data[1];
  } else {
    DB.hmi1.mode.report.val = CB.rx.data[2];
  }
}

void CAN_VCU_Trip_Mode_Read(void) {
  // read message
  if (DB.hmi1.mode.trip.sel == SW_M_TRIP_A) {
    DB.hmi1.mode.trip.val = BSL(CB.rx.data[3], 24) | BSL(CB.rx.data[2], 16) | BSL(CB.rx.data[1], 8) | CB.rx.data[0];
  } else {
    DB.hmi1.mode.trip.val = BSL(CB.rx.data[7], 24) | BSL(CB.rx.data[6], 16) | BSL(CB.rx.data[5], 8) | CB.rx.data[4];
  }
}

void CAN_MCU_Dummy_Read(void) {
  // read message
  DB.mcu.rpm = BSL(CB.rx.data[3], 24) | BSL(CB.rx.data[2], 16) | BSL(CB.rx.data[1], 8) | CB.rx.data[0];

  // convert RPM to Speed
  DB.vcu.speed = DB.mcu.rpm * MCU_SPEED_MAX / MCU_RPM_MAX;
}

void CAN_BMS_Dummy_Read(void) {
  // read message
  DB.bms.soc = CB.rx.data[0];
}
#endif

