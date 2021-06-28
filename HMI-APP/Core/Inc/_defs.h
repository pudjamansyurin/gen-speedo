/*
 * _database.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */

#ifndef DEFINES_H_
#define DEFINES_H_

/* Choose between VCU or Boot-loader mode */
#define APP 1

/* Includes
 * --------------------------------------------*/
#include "_defs_shared.h"

/* Exported constants
 * --------------------------------------------*/
#define HMI_VERSION ((uint16_t)347)

#define CAN_DEBUG 0

#define MCU_SPEED_MAX_KPH ((uint8_t)140)
#define MCU_DISCUR_MAX ((uint8_t)210)
#define BMS_LOWBAT_PERCENT ((uint8_t)20)

/* Exported enums
 * --------------------------------------------*/
typedef enum {
  HBAR_M_DRIVE = 0,
  HBAR_M_TRIP,
  HBAR_M_PREDICTION,
  HBAR_M_MAX = 3
} HBAR_MODE;

typedef enum {
  HBAR_M_DRIVE_ECONOMY = 0,
  HBAR_M_DRIVE_STANDARD,
  HBAR_M_DRIVE_SPORT,
  HBAR_M_DRIVE_MAX = 3,
} HBAR_MODE_DRIVE;

typedef enum {
  HBAR_M_TRIP_A = 0,
  HBAR_M_TRIP_B,
  HBAR_M_TRIP_ODO,
  HBAR_M_TRIP_MAX = 3,
} HBAR_MODE_TRIP;

typedef enum {
  HBAR_M_PREDICTION_RANGE = 0,
  HBAR_M_PREDICTION_EFFICIENCY,
  HBAR_M_PREDICTION_MAX = 2,
} HBAR_MODE_PREDICTION;

#endif /* DEFINES_H_ */
