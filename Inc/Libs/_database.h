/*
 * _database.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "main.h"
#include "_config.h"

// enum list
typedef enum {
	SWITCH_MODE_DRIVE = 0,
	SWITCH_MODE_TRIP = 1,
	SWITCH_MODE_REPORT = 2,
	SWITCH_MODE_MAX = 2
} switch_mode_t;

typedef enum {
	SWITCH_MODE_DRIVE_E = 0,
	SWITCH_MODE_DRIVE_S = 1,
	SWITCH_MODE_DRIVE_P = 2,
	SWITCH_MODE_DRIVE_MAX = 2
} switch_mode_drive_t;

typedef enum {
	SWITCH_MODE_TRIP_A = 0, SWITCH_MODE_TRIP_B = 1, SWITCH_MODE_TRIP_MAX = 1
} switch_mode_trip_t;

typedef enum {
	SWITCH_MODE_REPORT_RANGE = 0,
	SWITCH_MODE_REPORT_EFFICIENCY = 1,
	SWITCH_MODE_REPORT_MAX = 1
} switch_mode_report_t;

// struct list
typedef struct {
	switch_mode_t mode;
	switch_mode_drive_t mode_drive;
	switch_mode_trip_t mode_trip;
	uint32_t mode_trip_value;
	switch_mode_report_t mode_report;
	uint8_t mode_report_value;
} modes_t;

typedef struct {
	RTC_DateTypeDef date;
	RTC_TimeTypeDef time;
} timestamp_t;

typedef struct {
	uint8_t abs;
	uint8_t mirror;
	uint8_t lamp;
	uint8_t warning;
	uint8_t temperature;
	uint8_t finger;
	uint8_t keyless;
	uint8_t daylight;
	uint8_t sein_left;
	uint8_t sein_right;
} status_t;

#endif /* DATABASE_H_ */
