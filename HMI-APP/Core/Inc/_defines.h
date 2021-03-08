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
#define HMI_VERSION              (uint16_t) 340

// Some constants
#define MCU_SPEED_MAX 			      (uint8_t) 150
#define MCU_RPM_MAX 			       (uint32_t) 99999
#define VCU_ODOMETER_MAX		     (uint32_t) 99999

#define GUI_MAIN_COLOR			     (uint32_t) 0xFFC0C0C0
#define LCD_SIZE_X               (uint16_t) (320-1)
#define LCD_SIZE_Y               (uint16_t) (240-1)

// Events (for Individual Thread)
#define EVT_MASK				         (uint32_t) 0x7FFFFFFF

// Events group (for All Threads)
#define EVENT_MASK		  		     (uint32_t) 0xFFFFFF
#define EVENT_READY                         BIT(0)

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
    HBAR_M_DRIVE_PERFORMANCE,
    HBAR_M_DRIVE_MAX = 4,
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
