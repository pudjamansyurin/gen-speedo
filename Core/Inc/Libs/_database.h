/*
 * _database.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */

#ifndef DATABASE_H_
#define DATABASE_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

#define USE_HMI_LEFT 			  1
// Others Parameters
#define MCU_SPEED_MAX 			  200
#define MCU_RPM_MAX 			  99999
#define VCU_ODOMETER_MAX		  99999
#define HMI_DRIVE_MODE_MAX		  3
#define LCD_SIZE_X                (320-1)
#define LCD_SIZE_Y                (240-1)

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
#define BBR(var, x)               ((var >> x) & 0x01)
#define BBR2(var, x)              ((var >> x) & 0x03)

// list event
#define EVENT_CAN_RX_IT			  BIT(0)

/* Enum prototypes -------------------------------------------------------*/
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

/* Struct prototypes -------------------------------------------------------*/
typedef struct {
  sw_mode_t sel;
  uint8_t hide;
  sw_mode_drive_t drive;
  struct {
    sw_mode_trip_t sel;
    uint32_t val;
  } trip;
  struct {
    sw_mode_report_t sel;
    uint8_t val;
  } report;
} modes_t;

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

typedef struct {
  struct {
    uint8_t signal;
    uint8_t speed;
    uint32_t odometer;
  } vcu;
  struct {
    status_t status;
    modes_t mode;
  } hmi1;
  struct {
    uint8_t rpm;
  } mcu;
  struct {
    uint8_t soc;
  } bms;
} db_t;

typedef struct {
  GUI_CONST_STORAGE GUI_BITMAP *background;
  struct {
    GUI_POINT points[25];
    int count;
  } overlay;
} guiapp_t;

typedef struct {
  db_t db;
  struct {
    struct {
      uint8_t trip;
      uint8_t drive;
      uint8_t report;
    } mode;
    struct {
      uint8_t low;
      uint8_t update;
    } soc;
    struct {
      uint8_t low;
      TickType_t tick;
    } battery;
  } flag;
  uint8_t reset;
} latch_t;

/* Functions prototypes -------------------------------------------------------*/
void Reset_Database(void);

#endif /* DATABASE_H_ */
