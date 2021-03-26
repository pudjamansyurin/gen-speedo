/*
 * _database.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */

#ifndef DEFINES_H_
#define DEFINES_H_

/* Choose between VCU or Boot-loader mode */
#define BOOTLOADER                          0 

/* Includes ------------------------------------------------------------------*/
#include "_defines_shared.h"

/* Exported constants --------------------------------------------------------*/
#define HMI_VERSION              (uint16_t) 345

#define CAN_DEBUG		0

#define MCU_SPEED_MAX 			      (uint8_t) 150							// in kph
#define MCU_DISCUR_MAX 			       (uint8_t) 220
#define ODOMETER_MAX		         (uint32_t) 99999						// in km
#define BMS_LOWBAT							  (uint8_t) 20							// in %

/* Enum prototypes ------------------------------------------------------- */
typedef enum {
    HBAR_M_DRIVE = 0,
    HBAR_M_TRIP,
    HBAR_M_REPORT,
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
    HBAR_M_REPORT_RANGE = 0,
    HBAR_M_REPORT_AVERAGE,
    HBAR_M_REPORT_MAX = 2,
} HBAR_MODE_REPORT;

#endif /* DEFINES_H_ */
