/**
 *  \file _canbus.c
 *	\brief CAN bridge
 *	\details This file handle abstraction layer beetween application and can.c file
 *  \date Oct 11, 2019
 *  \author Puja
 */

#include "_canbus.h"

extern CAN_Rx RxCan;

// ==================================== ECU =========================================
#if (CAN_NODE & CAN_NODE_ECU)
uint8_t CANBUS_ECU_Switch(void) {
	CAN_Tx TxCan;
	extern switch_t DB_ECU_Switch[];
	extern uint8_t DB_MCU_Speed;
	extern timestamp_t DB_ECU_TimeStamp;
	extern uint32_t DB_ECU_Odometer;

	// set message
	TxCan.TxData[0] = DB_ECU_Switch[IDX_KEY_ABS].state;
	TxCan.TxData[0] |= DB_ECU_Switch[IDX_KEY_MIRRORING].state << 1;
	TxCan.TxData[0] |= DB_ECU_Switch[IDX_KEY_LAMP].state << 2;
	TxCan.TxData[0] |= 0 << 3;
	TxCan.TxData[0] |= 0 << 4;
	TxCan.TxData[0] |= 0 << 5;
	TxCan.TxData[0] |= 0 << 6;
	// check daylight (for auto brightness of HMI)
	TxCan.TxData[0] |= (DB_ECU_TimeStamp.time.Hours >= 5 && DB_ECU_TimeStamp.time.Hours <= 16) << 7;

	// sein
	TxCan.TxData[1] = DB_ECU_Switch[IDX_KEY_SEIN_LEFT].state << 0;
	TxCan.TxData[1] |= DB_ECU_Switch[IDX_KEY_SEIN_RIGHT].state << 1;

	// speed
	TxCan.TxData[2] = DB_MCU_Speed;

	// odometer
	TxCan.TxData[4] = (DB_ECU_Odometer & 0x000000FF);
	TxCan.TxData[5] = (DB_ECU_Odometer & 0x0000FF00) >> 8;
	TxCan.TxData[6] = (DB_ECU_Odometer & 0x00FF0000) >> 16;
	TxCan.TxData[7] = (DB_ECU_Odometer & 0xFF000000) >> 24;

	// dummy algorithm
	DB_ECU_Odometer = (DB_ECU_Odometer >= ECU_ODOMETER_MAX ? 0 : (DB_ECU_Odometer + 1));

	// set default header
	CAN_Set_Tx_Header(&(TxCan.TxHeader), CAN_ADDR_ECU_SWITCH, 8);
	// send message
	return CAN_Write(&TxCan);
}

uint8_t CANBUS_ECU_RTC(void) {
	CAN_Tx TxCan;
	extern timestamp_t DB_ECU_TimeStamp;

	// set message
	RTC_Read_RAW(&DB_ECU_TimeStamp);
	TxCan.TxData[0] = DB_ECU_TimeStamp.time.Seconds;
	TxCan.TxData[1] = DB_ECU_TimeStamp.time.Minutes;
	TxCan.TxData[2] = DB_ECU_TimeStamp.time.Hours;
	TxCan.TxData[3] = DB_ECU_TimeStamp.date.Date;
	TxCan.TxData[4] = DB_ECU_TimeStamp.date.Month;
	TxCan.TxData[5] = DB_ECU_TimeStamp.date.Year;
	TxCan.TxData[7] = DB_ECU_TimeStamp.date.WeekDay;

	// set default header
	CAN_Set_Tx_Header(&(TxCan.TxHeader), CAN_ADDR_ECU_RTC, 8);
	// send message
	return CAN_Write(&TxCan);
}

uint8_t CANBUS_ECU_Select_Set(void) {
	CAN_Tx TxCan;
	extern switcher_t DB_HMI_Switcher;

	// set message
	TxCan.TxData[0] = DB_HMI_Switcher.mode_sub[SWITCH_MODE_DRIVE];
	TxCan.TxData[0] |= DB_HMI_Switcher.mode_sub[SWITCH_MODE_TRIP] << 2;
	TxCan.TxData[0] |= DB_HMI_Switcher.mode_sub[SWITCH_MODE_REPORT] << 3;
	TxCan.TxData[0] |= DB_HMI_Switcher.mode << 4;

	TxCan.TxData[1] = DB_HMI_Switcher.mode_sub_report[SWITCH_MODE_REPORT_RANGE];
	TxCan.TxData[2] = DB_HMI_Switcher.mode_sub_report[SWITCH_MODE_REPORT_AVERAGE];

	// dummy algorithm
	if (!DB_HMI_Switcher.mode_sub_report[SWITCH_MODE_REPORT_RANGE]) {
		DB_HMI_Switcher.mode_sub_report[SWITCH_MODE_REPORT_RANGE] = 255;
	} else {
		DB_HMI_Switcher.mode_sub_report[SWITCH_MODE_REPORT_RANGE]--;
	}

	if (DB_HMI_Switcher.mode_sub_report[SWITCH_MODE_REPORT_AVERAGE] >= 255) {
		DB_HMI_Switcher.mode_sub_report[SWITCH_MODE_REPORT_AVERAGE] = 0;
	} else {
		DB_HMI_Switcher.mode_sub_report[SWITCH_MODE_REPORT_AVERAGE]++;
	}

	// set default header
	CAN_Set_Tx_Header(&(TxCan.TxHeader), CAN_ADDR_ECU_SELECT_SET, 3);
	// send message
	return CAN_Write(&TxCan);
}

uint8_t CANBUS_ECU_Trip_Mode(void) {
	CAN_Tx TxCan;
	extern switcher_t DB_HMI_Switcher;

	// set message
	TxCan.TxData[0] = (DB_HMI_Switcher.mode_sub_trip[SWITCH_MODE_TRIP_A] & 0x000000FF);
	TxCan.TxData[1] = (DB_HMI_Switcher.mode_sub_trip[SWITCH_MODE_TRIP_A] & 0x0000FF00) >> 8;
	TxCan.TxData[2] = (DB_HMI_Switcher.mode_sub_trip[SWITCH_MODE_TRIP_A] & 0x00FF0000) >> 16;
	TxCan.TxData[3] = (DB_HMI_Switcher.mode_sub_trip[SWITCH_MODE_TRIP_A] & 0xFF000000) >> 24;
	TxCan.TxData[4] = (DB_HMI_Switcher.mode_sub_trip[SWITCH_MODE_TRIP_B] & 0x000000FF);
	TxCan.TxData[5] = (DB_HMI_Switcher.mode_sub_trip[SWITCH_MODE_TRIP_B] & 0x0000FF00) >> 8;
	TxCan.TxData[6] = (DB_HMI_Switcher.mode_sub_trip[SWITCH_MODE_TRIP_B] & 0x00FF0000) >> 16;
	TxCan.TxData[7] = (DB_HMI_Switcher.mode_sub_trip[SWITCH_MODE_TRIP_B] & 0xFF000000) >> 24;

	// dummy algorithm
	if (DB_HMI_Switcher.mode_sub_trip[DB_HMI_Switcher.mode_sub[DB_HMI_Switcher.mode]] >= ECU_ODOMETER_MAX) {
		DB_HMI_Switcher.mode_sub_trip[DB_HMI_Switcher.mode_sub[DB_HMI_Switcher.mode]] = 0;
	} else {
		DB_HMI_Switcher.mode_sub_trip[DB_HMI_Switcher.mode_sub[DB_HMI_Switcher.mode]]++;
	}

	// set default header
	CAN_Set_Tx_Header(&(TxCan.TxHeader), CAN_ADDR_ECU_TRIP_MODE, 8);
	// send message
	return CAN_Write(&TxCan);
}

#endif

// ==================================== MCU =========================================
#if (CAN_NODE & CAN_NODE_MCU)
uint8_t CANBUS_MCU_Dummy(void) {
	CAN_Tx TxCan;
	extern uint16_t MCU_RPM;
	static uint8_t MCU_Temperature = 0;

	// set message
	// RPM data
	TxCan.TxData[0] = (MCU_RPM & 0x00FF);
	TxCan.TxData[1] = (MCU_RPM & 0xFF00) >> 8;
	// Temperature data
	TxCan.TxData[2] = MCU_Temperature;

	// dummy algorithm
	MCU_Temperature++;

	// set default header
	CAN_Set_Tx_Header(&(TxCan.TxHeader), CAN_ADDR_MCU_DUMMY, 3);

	// send message
	return CAN_Write(&TxCan);
}
#endif

// ==================================== BMS =========================================
#if (CAN_NODE & CAN_NODE_BMS)
uint8_t CANBUS_BMS_Dummy(void) {
	CAN_Tx TxCan;
	static uint8_t BMS_SoC = 100;
	static uint8_t BMS_Temperature = 0;

	// set message
	// SoC data
	TxCan.TxData[0] = BMS_SoC;
	// Temperature data
	TxCan.TxData[1] = BMS_Temperature++;

	// dummy algorithm
	BMS_SoC = (!BMS_SoC ? 100 : (BMS_SoC - 1));

	// set default header
	CAN_Set_Tx_Header(&(TxCan.TxHeader), CAN_ADDR_BMS_DUMMY, 2);

	// send message
	return CAN_Write(&TxCan);
}
#endif

// ==================================== HMI =========================================
#if (CAN_NODE & CAN_NODE_HMI)
uint8_t CANBUS_HMI_Heartbeat(void) {
	CAN_Tx TxCan;

	// set default header
	CAN_Set_Tx_Header(&(TxCan.TxHeader), CAN_ADDR_HMI_DUMMY + (USE_HMI_LEFT ? 1 : 0), 1);
	TxCan.TxHeader.RTR = CAN_RTR_REMOTE;

	// send message
	return CAN_Write(&TxCan);
}

/* ------------------------------------ READER ------------------------------------- */
void CANBUS_ECU_Switch_Read(void) {
	extern status_t DB_HMI_Status;
	extern uint32_t DB_ECU_Odometer;
	extern uint8_t DB_ECU_Signal;

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
	DB_ECU_Signal = RxCan.RxData[2];

	// odometer
	DB_ECU_Odometer = (RxCan.RxData[7] << 24) | (RxCan.RxData[6] << 16) | (RxCan.RxData[5] << 8) | RxCan.RxData[4];
}

void CANBUS_ECU_RTC_Read(void) {
	extern timestamp_t DB_ECU_TimeStamp;

	// read message
	DB_ECU_TimeStamp.time.Seconds = RxCan.RxData[0];
	DB_ECU_TimeStamp.time.Minutes = RxCan.RxData[1];
	DB_ECU_TimeStamp.time.Hours = RxCan.RxData[2];
	DB_ECU_TimeStamp.date.Date = RxCan.RxData[3];
	DB_ECU_TimeStamp.date.Month = RxCan.RxData[4];
	DB_ECU_TimeStamp.date.Year = RxCan.RxData[5];
	DB_ECU_TimeStamp.date.WeekDay = RxCan.RxData[7];
}

void CANBUS_ECU_Select_Set_Read(void) {
	extern modes_t DB_HMI_Mode;

	// read message
	DB_HMI_Mode.mode_drive = RxCan.RxData[0] & 0x03;
	DB_HMI_Mode.mode_trip = (RxCan.RxData[0] >> 2) & 0x01;
	DB_HMI_Mode.mode_report = (RxCan.RxData[0] >> 3) & 0x01;
	DB_HMI_Mode.mode = (RxCan.RxData[0] >> 4) & 0x03;

	if (DB_HMI_Mode.mode_report == SWITCH_MODE_REPORT_RANGE) {
		DB_HMI_Mode.mode_report_value = RxCan.RxData[1];
	} else {
		DB_HMI_Mode.mode_report_value = RxCan.RxData[2];
	}
}

void CANBUS_ECU_Trip_Mode_Read(void) {
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
	extern uint8_t DB_ECU_Speed;
	extern uint8_t DB_MCU_Temperature;

	// read message
	DB_MCU_RPM = (RxCan.RxData[3] << 24 | RxCan.RxData[2] << 16 | RxCan.RxData[1] << 8 | RxCan.RxData[0]);
	DB_MCU_Temperature = RxCan.RxData[4];

	// convert RPM to Speed
	DB_ECU_Speed = DB_MCU_RPM * MCU_SPEED_MAX / MCU_RPM_MAX;
}

void CANBUS_BMS_Dummy_Read(void) {
	extern uint8_t DB_BMS_SoC;
	extern uint8_t DB_BMS_Temperature;

	// read message
	DB_BMS_SoC = RxCan.RxData[0];
	DB_BMS_Temperature = RxCan.RxData[1];
}
#endif

