/*
 * _database.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */

#ifndef DEFINES_SHARED_H_
#define DEFINES_SHARED_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#if (!BOOTLOADER)
#include "cmsis_os.h"
#endif

/* Exported constants --------------------------------------------------------*/
// macro to manipulate bit
#define BIT(x)                              (1ULL << x)
#define BV(var, x)                          (var |= (1ULL << x))
#define BC(var, x)                          (var &= ~(1ULL << x))
#define BT(var, x)                          (var ^= (1ULL << x))
//#define _L(var, x)                          (var << x)
//#define _R(var, x)                          (var >> x)
#define _R1(var, x)                         ((var >> x) & 0x01)
#define _R2(var, x)                         ((var >> x) & 0x03)
#define _R8(var, x)                         ((var >> x) & 0xFF)

// FOTA realated stuff
#define SRAM_SIZE                    (uint32_t) 0x30000
#define SRAM_BASE_ADDR               (uint32_t) 0x20000000
#define SRAM_END_ADDR                           (SRAM_BASE_ADDR + SRAM_SIZE)
#define SP_MASK                      (uint32_t) 0x2FFFFFFF
#define SP_RANGE                                (SP_MASK - (SRAM_SIZE - 1))
#define IAP_FLAG                     (uint32_t) 0xAABBCCDD
#define IAP_FLAG_ADDR                           (SRAM_END_ADDR - 4)
#define IS_VALID_SP(a)                          ((*(__IO uint32_t*)a & SP_RANGE) == SRAM_BASE_ADDR)

// Some constants
#if (!BOOTLOADER)
#define MCU_SPEED_MAX 			      (uint8_t) 150
#define MCU_RPM_MAX 			     (uint32_t) 99999
#define VCU_ODOMETER_MAX		     (uint32_t) 99999

#define GUI_MAIN_COLOR			     (uint32_t) 0xFFC0C0C0
#define LCD_SIZE_X                   (uint16_t) (320-1)
#define LCD_SIZE_Y                   (uint16_t) (240-1)

// Events (for Individual Thread)
#define EVT_MASK				     (uint32_t) 0x7FFFFFFF

// Events group (for All Threads)
#define EVENT_MASK		  		     (uint32_t) 0xFFFFFF
#define EVENT_READY                  BIT(0)
#endif

// CAN Message Address
#define CAND_VCU_SWITCH			     (uint32_t) 0x000
#define CAND_VCU_DATETIME		     (uint32_t) 0x001
#define CAND_VCU_SELECT_SET		     (uint32_t) 0x002
#define CAND_VCU_TRIP_MODE		     (uint32_t) 0x003
#define CAND_HMI1                    (uint32_t) 0x7C0
// FOCAN Command Address
#define CAND_SET_PROGRESS            (uint32_t) 0x101
#if (BOOTLOADER)
#define CAND_GET_CHECKSUM            (uint32_t) 0x102
#define CAND_PRA_DOWNLOAD            (uint32_t) 0x103
#define CAND_INIT_DOWNLOAD           (uint32_t) 0x104
#define CAND_DOWNLOADING             (uint32_t) 0x105
#define CAND_PASCA_DOWNLOAD          (uint32_t) 0x106
#endif

/* Enum prototypes ------------------------------------------------------- */
#if (BOOTLOADER)
typedef enum {
    IAP_VCU = 0xA1B2C3D4,
    IAP_HMI = 0x1A2B3C4D
} IAP_TYPE;

typedef enum {
    FOCAN_ERROR = 0x00,
    FOCAN_ACK = 0x79,
    FOCAN_NACK = 0x1F
} FOCAN;
#else
typedef enum {
    SW_M_DRIVE = 0,
    SW_M_TRIP,
    SW_M_REPORT,
    SW_M_MAX = 2
} SW_MODE;

typedef enum {
    SW_M_DRIVE_ECONOMY = 0,
    SW_M_DRIVE_STANDARD,
    SW_M_DRIVE_SPORT,
    SW_M_DRIVE_PERFORMANCE,
    SW_M_DRIVE_MAX = 3,
} SW_MODE_DRIVE;

typedef enum {
    SW_M_TRIP_ODO = 0,
    SW_M_TRIP_A,
    SW_M_TRIP_B,
    SW_M_TRIP_MAX = 2,
} SW_MODE_TRIP;

typedef enum {
    SW_M_REPORT_RANGE = 0,
    SW_M_REPORT_AVERAGE,
    SW_M_REPORT_MAX = 1,
} SW_MODE_REPORT;
#endif

#endif /* DEFINES_SHARED_H_ */
