/**
 *  \file _canbus.c
 *	\brief CAN bridge
 *	\details This file handle abstraction layer beetween application and can.c file
 *  \date Oct 11, 2019
 *  \author Puja
 */

#include "_canbus.h"

CAN_Tx TxCan;
extern CAN_Rx RxCan;

// ==================================== HMI =========================================
#if (CAN_NODE & CAN_NODE_HMI)
uint8_t CANBUS_HMI_Heartbeat(void) {
	// set default header
	CAN_Set_Tx_Header(&(TxCan.TxHeader), CAN_ADDR_HMI_DUMMY + (USE_HMI_LEFT ? 1 : 0), 1);
	TxCan.TxHeader.RTR = CAN_RTR_REMOTE;

	// send message
	return CAN_Write(&TxCan);
}

/* ------------------------------------ READER ------------------------------------- */
void CANBUS_VCU_Switch_Read(void) {
	extern status_t DB_HMI_Status;
	extern uint32_t DB_VCU_Odometer;
	extern uint8_t DB_VCU_Signal;

	// read message
	DB_HMI_Status.abs = RxCan.RxData[0] & 0x01;
	DB_HMI_Status.mirror = (RxCan.RxData[0] >> 1) & 0x01;
	DB_HMI_Status.lamp = (RxCan.RxData[0] >> 2) & 0x01;
	DB_HMI_Status.warning = (RxCan.RxData[0] >> 3) & 0x01;
	DB_HMI_Status.temperature = (RxCan.RxData[0] >> 4) & 0x01;
	DB_HMI_Status.finger = (RxCan.RxData[0] >> 5) & 0x01;
	DB_HMI_Status.keyless = (RxCan.RxData[0] >> 6) & 0x01;
	DB_HMI_Status.daylight = (RxCan.RxData[0] >> 7) & 0x01;

	// sein
	DB_HMI_Status.sein_left = RxCan.RxData[1] & 0x01;
	DB_HMI_Status.sein_right = (RxCan.RxData[1] >> 1) & 0x01;

	// signal
	DB_VCU_Signal = RxCan.RxData[2];

	// odometer
	DB_VCU_Odometer = (RxCan.RxData[7] << 24) | (RxCan.RxData[6] << 16) | (RxCan.RxData[5] << 8) | RxCan.RxData[4];
}

void CANBUS_VCU_Select_Set_Read(void) {
	extern modes_t DB_HMI_Mode;

	// read message
	DB_HMI_Mode.mode_drive = RxCan.RxData[0] & 0x03;
	DB_HMI_Mode.mode_trip = (RxCan.RxData[0] >> 2) & 0x01;
	DB_HMI_Mode.mode_report = (RxCan.RxData[0] >> 3) & 0x01;
	DB_HMI_Mode.mode = (RxCan.RxData[0] >> 4) & 0x03;
	DB_HMI_Mode.hide = (RxCan.RxData[0] >> 6) & 0x01;

	// decide report value according to mode
	if (DB_HMI_Mode.mode_report == SWITCH_MODE_REPORT_RANGE) {
		DB_HMI_Mode.mode_report_value = RxCan.RxData[1];
	} else {
		DB_HMI_Mode.mode_report_value = RxCan.RxData[2];
	}
}

void CANBUS_VCU_Trip_Mode_Read(void) {
	extern modes_t DB_HMI_Mode;

	// read message
	if (DB_HMI_Mode.mode_trip == SWITCH_MODE_TRIP_A) {
		DB_HMI_Mode.mode_trip_value = (RxCan.RxData[3] << 24) | (RxCan.RxData[2] << 16) | (RxCan.RxData[1] << 8) | RxCan.RxData[0];
	} else {
		DB_HMI_Mode.mode_trip_value = (RxCan.RxData[7] << 24) | (RxCan.RxData[6] << 16) | (RxCan.RxData[5] << 8) | RxCan.RxData[4];
	}
}

void CANBUS_MCU_Dummy_Read(void) {
	extern uint32_t DB_MCU_RPM;
	extern uint8_t DB_VCU_Speed;

	// read message
	DB_MCU_RPM = (RxCan.RxData[3] << 24 | RxCan.RxData[2] << 16 | RxCan.RxData[1] << 8 | RxCan.RxData[0]);

	// convert RPM to Speed
	DB_VCU_Speed = DB_MCU_RPM * MCU_SPEED_MAX / MCU_RPM_MAX;
}

void CANBUS_BMS_Dummy_Read(void) {
	extern uint8_t DB_BMS_SoC;

	// read message
	DB_BMS_SoC = RxCan.RxData[0];
}
#endif

