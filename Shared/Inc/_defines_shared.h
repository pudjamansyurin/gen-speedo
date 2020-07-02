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
#include "GUI.h"
#endif

/* Exported constants --------------------------------------------------------*/
#define LD1_PORT                            (USE_HMI_LEFT ? LEFT_LD1_GPIO_Port : RIGHT_LD1_GPIO_Port)
#define LD1_PIN                             (USE_HMI_LEFT ? LEFT_LD1_Pin : RIGHT_LD1_Pin)
#define LD2_PORT                            (USE_HMI_LEFT ? LEFT_LD2_GPIO_Port : RIGHT_LD2_GPIO_Port)
#define LD2_PIN                             (USE_HMI_LEFT ? LEFT_LD2_Pin : RIGHT_LD2_Pin)

// macro to manipulate bit
#define BIT(x)                              (1ULL << x)
#define BV(var, x)                          (var |= (1ULL << x))
#define BC(var, x)                          (var &= ~(1ULL << x))
#define BT(var, x)                          (var ^= (1ULL << x))
#define _L(var, x)                          (var << x)
#define _R(var, x)                          (var >> x)
#define _R1(var, x)                         ((var >> x) & 0x01)
#define _R2(var, x)                         ((var >> x) & 0x03)
#define _R8(var, x)                         ((var >> x) & 0xFF)

// FOTA realated stuff
#define SRAM_SIZE               (uint32_t) 0x30000
#define SRAM_BASE_ADDR          (uint32_t) 0x20000000
#define SRAM_END_ADDR                      (SRAM_BASE_ADDR + SRAM_SIZE)
#define SP_MASK                 (uint32_t) 0x2FFFFFFF
#define SP_RANGE                           (SP_MASK - (SRAM_SIZE - 1))
#define IAP_FLAG                (uint32_t) 0xAABBCCDD
#define IAP_FLAG_ADDR                      (SRAM_END_ADDR - sizeof(uint32_t))
#define IS_VALID_SP(a)          ((*(__IO uint32_t*)a & SP_RANGE) == SRAM_BASE_ADDR)

// Some constants
#if (!BOOTLOADER)
#define MCU_SPEED_MAX 			  (uint8_t) 255
#define MCU_RPM_MAX 			 (uint32_t) 99999
#define VCU_ODOMETER_MAX		 (uint32_t) 99999

#define GUI_MAIN_COLOR			 (uint32_t) 0xFFC0C0C0
#define LCD_SIZE_X               (uint16_t) (320-1)
#define LCD_SIZE_Y               (uint16_t) (240-1)

// Events (for Individual Thread)
#define EVT_MASK				 (uint32_t) 0x7FFFFFFF
#define EVT_CAN_RX_IT			            BIT(0)
#define EVT_DISPLAY_UPDATE                  BIT(0)

// Events group (for All Threads)
#define EVENT_MASK		  		 (uint32_t) 0xFFFFFF
#define EVENT_READY                         BIT(0)

// CAN Message Address
#define CAND_VCU_SWITCH			 (uint32_t) 0x000
#define CAND_VCU_DATETIME		 (uint32_t) 0x001
#define CAND_VCU_SELECT_SET		 (uint32_t) 0x002
#define CAND_VCU_TRIP_MODE		 (uint32_t) 0x003
#endif
#define CAND_HMI1_LEFT           (uint32_t) 0x7C0
#define CAND_HMI1_RIGHT          (uint32_t) 0x7C1

#define CAN_MY_ADRESS                       (USE_HMI_LEFT ? CAND_HMI1_LEFT : CAND_HMI1_RIGHT)

// FOCAN Command Address
#define CAND_ENTER_IAP               (uint32_t) 0x100
#if (BOOTLOADER)
#define CAND_GET_CHECKSUM            (uint32_t) 0x101

/* Enum prototypes ------------------------------------------------------- */
typedef enum {
    FOCAN_ACK = 0x79,
    FOCAN_NACK = 0x1F
} FOCAN;

#else
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
    SW_M_REPORT_EFFICIENCY = 1,
    SW_M_REPORT_MAX = 1,
} sw_mode_report_t;
#endif

#endif /* DEFINES_SHARED_H_ */
