/*
 * _database.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */

#ifndef DEFINES_H_
#define DEFINES_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Exported constants --------------------------------------------------------*/
#define USE_HMI_LEFT 					  	1

#define MCU_SPEED_MAX 			  		255U
#define MCU_RPM_MAX 			 			 	99999U
#define VCU_ODOMETER_MAX		  		99999U

#define GUI_MAIN_COLOR						0xFFC0C0C0
#define LCD_SIZE_X                (320-1)
#define LCD_SIZE_Y                (240-1)

#define LD1_PORT                  (USE_HMI_LEFT ? LEFT_LD1_GPIO_Port : RIGHT_LD1_GPIO_Port)
#define LD1_PIN                   (USE_HMI_LEFT ? LEFT_LD1_Pin : RIGHT_LD1_Pin)
#define LD2_PORT                  (USE_HMI_LEFT ? LEFT_LD2_GPIO_Port : RIGHT_LD2_GPIO_Port)
#define LD2_PIN                   (USE_HMI_LEFT ? LEFT_LD2_Pin : RIGHT_LD2_Pin)

// macro to manipulate bit
#define BIT(x)                    (1ULL << x)
#define BV(var, x)                (var |= (1ULL << x))
#define BC(var, x)                (var &= ~(1ULL << x))
#define BT(var, x)                (var ^= (1ULL << x))
#define _L(var, x)                (var << x)
#define _R(var, x)                (var >> x)
#define _R1(var, x)               ((var >> x) & 0x01)
#define _R2(var, x)               ((var >> x) & 0x03)
#define _R8(var, x)               ((var >> x) & 0xFF)

// Events (for Individual Thread)
#define EVT_MASK									0x7FFFFFFF
#define EVT_CAN_RX_IT			  			BIT(0)
#define EVT_DISPLAY_UPDATE        BIT(0)

// Events group (for All Threads)
#define EVENT_MASK								0xFFFFFF
#define EVENT_READY               BIT(0)

// CAN Message Address
#define CAND_VCU_SWITCH					 	0x000
#define CAND_VCU_DATETIME				 	0x001
#define CAND_VCU_SELECT_SET			 	0x002
#define CAND_VCU_TRIP_MODE			 	0x003

#define CAND_HMI1_LEFT            0x7C0
#define CAND_HMI1_RIGHT           0x7C1

#if USE_HMI_LEFT
#define CAN_MY_ADRESS             CAND_HMI1_LEFT
#else
#define CAN_MY_ADRESS             CAND_HMI1_RIGHT
#endif

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
    SW_M_REPORT_EFFICIENCY = 1,
    SW_M_REPORT_MAX = 1,
} sw_mode_report_t;

/* Functions prototypes -------------------------------------------------------*/
void Reset_Database(void);

#endif /* DEFINES_H_ */
