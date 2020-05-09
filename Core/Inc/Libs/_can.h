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
#define CAND_VCU_SWITCH					 												0x000
#define CAND_VCU_RTC						 												0x001
#define CAND_VCU_SELECT_SET			 												0x002
#define CAND_VCU_TRIP_MODE			 												0x003

#define CAND_HMI1_LEFT                                  0x7C0
#define CAND_HMI1_RIGHT                                 0x7C1

#define CAND_MCU_DUMMY																	0x7A0
#define CAND_BMS_DUMMY																	0x7B0

#if USE_HMI_LEFT
#define CAN_MY_ADRESS                                   CAND_HMI1_LEFT
#else
#define CAN_MY_ADRESS                                   CAND_HMI1_RIGHT
#endif

/* Function prototype --------------------------------------------------------*/
uint8_t CAN_HMI_Heartbeat(void);
void CAN_VCU_Switch_Read(void);
void CAN_VCU_Select_Set_Read(void);
void CAN_VCU_Trip_Mode_Read(void);

#endif /* CAN_H_ */
