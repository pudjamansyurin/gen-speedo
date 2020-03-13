/*
 * _can.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */

#ifndef CAN_H_
#define CAN_H_

/* Includes ------------------------------------------------------------------*/
#include "_utils.h"
#include "_canbus.h"

// CAN Message Address
#define CAN_ADDR_VCU_SWITCH					 				0x000
#define CAN_ADDR_VCU_RTC						 			0x001
#define CAN_ADDR_VCU_SELECT_SET			 					0x002
#define CAN_ADDR_VCU_TRIP_MODE			 					0x003
#define CAN_ADDR_MCU_DUMMY									0x7A0
#define CAN_ADDR_BMS_DUMMY									0x7B0
#define CAN_ADDR_HMI_DUMMY									0x7C0

/* Function prototype --------------------------------------------------------*/
uint8_t CAN_HMI_Heartbeat(void);
void CAN_VCU_Switch_Read(void);
void CAN_VCU_Select_Set_Read(void);
void CAN_VCU_Trip_Mode_Read(void);
void CAN_MCU_Dummy_Read(void);
void CAN_BMS_Dummy_Read(void);

#endif /* CAN_H_ */
