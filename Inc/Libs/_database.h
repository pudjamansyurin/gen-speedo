/*
 * _database.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "main.h"

#define USE_HMI_LEFT 							0
#define LD1_PORT                  (USE_HMI_LEFT ? LEFT_LD1_GPIO_Port : RIGHT_LD1_GPIO_Port)    
#define LD1_PIN                   (USE_HMI_LEFT ? LEFT_LD1_Pin : RIGHT_LD1_Pin)    
#define LD2_PORT                  (USE_HMI_LEFT ? LEFT_LD2_GPIO_Port : RIGHT_LD2_GPIO_Port)
#define LD2_PIN                   (USE_HMI_LEFT ? LEFT_LD2_Pin : RIGHT_LD2_Pin)               

// macro to manipulate bit
#define BIT(x)                    (1 << x)
#define BV(var, x)                (var |= (1 << x))
#define BC(var, x)                (var &= ~(1 << x))
#define BT(var, x)                (var ^= (1 << x))
#define BSL(var, x)               (var << x)
#define BSR(var, x)               ((var >> x) & 0xFF)

// list event
#define EVENT_CAN_RX_IT						BIT(0)

// enum list
typedef enum {
  SW_M_DRIVE = 0,
  SW_M_TRIP = 1,
  SW_M_REPORT = 2,
  SW_M_MAX = 2
} sw_mode_t;

typedef enum {
  SW_M_DRIVE_E = 0,
  SW_M_DRIVE_S = 1,
  SW_M_DRIVE_P = 2,
  SW_M_DRIVE_MAX = 2,
  SW_M_DRIVE_R = 3,
} sw_mode_drive_t;

typedef enum {
  SW_M_TRIP_A = 0,
  SW_M_TRIP_B = 1,
  SW_M_TRIP_MAX = 1,
} sw_mode_trip_t;

typedef enum {
  SW_M_REPORT_RANGE = 0,
  SW_M_REPORT_AVERAGE = 1,
  SW_M_REPORT_MAX = 1,
} sw_mode_report_t;

// struct list
typedef struct {
  sw_mode_t mode;
  uint8_t hide;
  sw_mode_drive_t mode_drive;
  sw_mode_trip_t mode_trip;
  uint32_t mode_trip_value;
  sw_mode_report_t mode_report;
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
