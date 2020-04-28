/**
 *  \file _canbus.c
 *	\brief CAN bridge
 *	\details This file handle abstraction layer beetween application and can.c file
 *  \date Oct 11, 2019
 *  \author Puja
 */
/* Includes ------------------------------------------------------------------*/
#include "_can.h"
#include "_utils.h"

/* External variables --------------------------------------------------------*/
extern canbus_t CB;
extern db_t DB;

/* Functions implementation --------------------------------------------------*/
uint8_t CAN_HMI_Heartbeat(void) {
  // set default header
  CANBUS_Header(&(CB.tx.header), CAN_MY_ADRESS, 1);
  CB.tx.header.RTR = CAN_RTR_REMOTE;

  // send message
  return CANBUS_Write(&(CB.tx));
}

/* ------------------------------------ READER ------------------------------------- */
void CAN_VCU_Switch_Read(void) {
  // read message
  DB.hmi1.status.abs = _R1(CB.rx.data.u8[0], 0);
  DB.hmi1.status.mirror = _R1(CB.rx.data.u8[0], 1);
  DB.hmi1.status.lamp = _R1(CB.rx.data.u8[0], 2);
  DB.hmi1.status.warning = _R1(CB.rx.data.u8[0], 3);
  DB.hmi1.status.temperature = _R1(CB.rx.data.u8[0], 4);
  DB.hmi1.status.finger = _R1(CB.rx.data.u8[0], 5);
  DB.hmi1.status.keyless = _R1(CB.rx.data.u8[0], 6);
  DB.hmi1.status.daylight = _R1(CB.rx.data.u8[0], 7);

  // sein
  DB.hmi1.status.sein_left = _R1(CB.rx.data.u8[1], 0);
  DB.hmi1.status.sein_right = _R1(CB.rx.data.u8[1], 1);

  // signal
  DB.vcu.signal = CB.rx.data.u8[2];
  DB.bms.soc = CB.rx.data.u8[3];

  // odometer
  DB.vcu.odometer = CB.rx.data.u32[1];

  // update backlight state
  _SetBacklight(DB.hmi1.status.daylight);
}

void CAN_VCU_Select_Set_Read(void) {
  // read message
  DB.hmi1.mode.drive = _R2(CB.rx.data.u8[0], 0);
  DB.hmi1.mode.trip.sel = _R1(CB.rx.data.u8[0], 2);
  DB.hmi1.mode.report.sel = _R1(CB.rx.data.u8[0], 3);
  DB.hmi1.mode.sel = _R2(CB.rx.data.u8[0], 4);
  DB.hmi1.mode.hide = _R1(CB.rx.data.u8[0], 6);

  // decide report value according to mode
  if (DB.hmi1.mode.report.sel == SW_M_REPORT_RANGE) {
    DB.hmi1.mode.report.val = CB.rx.data.u8[1];
  } else {
    DB.hmi1.mode.report.val = CB.rx.data.u8[2];
  }
}

void CAN_VCU_Trip_Mode_Read(void) {
  // read message
  if (DB.hmi1.mode.trip.sel == SW_M_TRIP_A) {
    DB.hmi1.mode.trip.val = CB.rx.data.u32[0];
  } else {
    DB.hmi1.mode.trip.val = CB.rx.data.u32[1];
  }
}

void CAN_MCU_Dummy_Read(void) {
  // read message
  DB.mcu.rpm = CB.rx.data.u16[0];
  DB.mcu.temperature = CB.rx.data.u16[1];

  // convert RPM to Speed
  DB.vcu.speed = DB.mcu.rpm * MCU_SPEED_MAX / MCU_RPM_MAX;
}

