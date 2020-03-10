/**
 *  \file _canbus.c
 *	\brief CAN bridge
 *	\details This file handle abstraction layer beetween application and can.c file
 *  \date Oct 11, 2019
 *  \author Puja
 */

#include "_can.h"

extern uint32_t DB_VCU_Odometer;
extern uint8_t DB_VCU_Signal;
extern uint8_t DB_VCU_Speed;
extern status_t DB_HMI_Status;
extern modes_t DB_HMI_Mode;
extern uint32_t DB_MCU_RPM;
extern uint8_t DB_BMS_SoC;
extern canbus_t CB;

// ==================================== HMI =========================================
#if (CAN_NODE & CAN_NODE_HMI)
uint8_t CANBUS_HMI_Heartbeat(void) {
  // set default header
  CANBUS_Header(&(CB.tx.header), CAN_ADDR_HMI_DUMMY + (USE_HMI_LEFT ? 1 : 0), 1);
  CB.tx.header.RTR = CAN_RTR_REMOTE;

  // send message
  return CANBUS_Write(&(CB.tx));
}

/* ------------------------------------ READER ------------------------------------- */
void CANBUS_VCU_Switch_Read(void) {
  // read message
  DB_HMI_Status.abs = CB.rx.data[0] & 0x01;
  DB_HMI_Status.mirror = (CB.rx.data[0] >> 1) & 0x01;
  DB_HMI_Status.lamp = (CB.rx.data[0] >> 2) & 0x01;
  DB_HMI_Status.warning = (CB.rx.data[0] >> 3) & 0x01;
  DB_HMI_Status.temperature = (CB.rx.data[0] >> 4) & 0x01;
  DB_HMI_Status.finger = (CB.rx.data[0] >> 5) & 0x01;
  DB_HMI_Status.keyless = (CB.rx.data[0] >> 6) & 0x01;
  DB_HMI_Status.daylight = (CB.rx.data[0] >> 7) & 0x01;

  // sein
  DB_HMI_Status.sein_left = CB.rx.data[1] & 0x01;
  DB_HMI_Status.sein_right = (CB.rx.data[1] >> 1) & 0x01;

  // signal
  DB_VCU_Signal = CB.rx.data[2];

  // odometer
  DB_VCU_Odometer = (CB.rx.data[7] << 24) | (CB.rx.data[6] << 16) | (CB.rx.data[5] << 8) | CB.rx.data[4];
}

void CANBUS_VCU_Select_Set_Read(void) {
  // read message
  DB_HMI_Mode.mode_drive = CB.rx.data[0] & 0x03;
  DB_HMI_Mode.mode_trip = (CB.rx.data[0] >> 2) & 0x01;
  DB_HMI_Mode.mode_report = (CB.rx.data[0] >> 3) & 0x01;
  DB_HMI_Mode.mode = (CB.rx.data[0] >> 4) & 0x03;
  DB_HMI_Mode.hide = (CB.rx.data[0] >> 6) & 0x01;

  // decide report value according to mode
  if (DB_HMI_Mode.mode_report == SW_M_REPORT_RANGE) {
    DB_HMI_Mode.mode_report_value = CB.rx.data[1];
  } else {
    DB_HMI_Mode.mode_report_value = CB.rx.data[2];
  }
}

void CANBUS_VCU_Trip_Mode_Read(void) {
  // read message
  if (DB_HMI_Mode.mode_trip == SW_M_TRIP_A) {
    DB_HMI_Mode.mode_trip_value = (CB.rx.data[3] << 24) | (CB.rx.data[2] << 16) | (CB.rx.data[1] << 8) | CB.rx.data[0];
  } else {
    DB_HMI_Mode.mode_trip_value = (CB.rx.data[7] << 24) | (CB.rx.data[6] << 16) | (CB.rx.data[5] << 8) | CB.rx.data[4];
  }
}

void CANBUS_MCU_Dummy_Read(void) {
  // read message
  DB_MCU_RPM = (CB.rx.data[3] << 24 | CB.rx.data[2] << 16 | CB.rx.data[1] << 8 | CB.rx.data[0]);

  // convert RPM to Speed
  DB_VCU_Speed = DB_MCU_RPM * MCU_SPEED_MAX / MCU_RPM_MAX;
}

void CANBUS_BMS_Dummy_Read(void) {
  // read message
  DB_BMS_SoC = CB.rx.data[0];
}
#endif

