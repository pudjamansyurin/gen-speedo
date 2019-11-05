/*
 * _database.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */

#include "_database.h"

// @formatter:off
modes_t DB_HMI_Mode = {
		SWITCH_MODE_TRIP,
		SWITCH_MODE_DRIVE_E,
		SWITCH_MODE_TRIP_A,
		0,
		SWITCH_MODE_REPORT_RANGE,
		0
};
// @formatter:on
status_t DB_HMI_Status;
uint32_t DB_ECU_Odometer = 0;
timestamp_t DB_ECU_TimeStamp;
uint8_t DB_ECU_Speed = 0;
uint32_t DB_MCU_RPM = 0;
uint8_t DB_MCU_Temperature = 0;
uint8_t DB_BMS_SoC = 0;
uint8_t DB_BMS_Temperature = 0;
