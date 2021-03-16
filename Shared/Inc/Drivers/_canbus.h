/*
 * _can.h
 *
 *  Created on: Oct 7, 2019
 *      Author: Puja
 */

#ifndef CANBUS_H_
#define CANBUS_H_

/* Includes ------------------------------------------------------------------*/
#include "Libs/_utils.h"

#define CAN_DATA 					UNION64

/* Exported defines -----------------------------------------------------------*/
typedef enum {
	CAND_FOCAN_PROGRESS 		= 0x031,
	CAND_FOCAN_CRC 					= 0x032,
	CAND_FOCAN_PRA 					= 0x033,
	CAND_FOCAN_INIT 				= 0x034,
	CAND_FOCAN_RUNNING 			= 0x035,
	CAND_FOCAN_PASCA 				= 0x036,

	CAND_VCU_SWITCH 				= 0x050,
	CAND_VCU_DATETIME 			= 0x051,
	CAND_VCU_SELECT_SET 		= 0x052,
	CAND_VCU_TRIP_MODE 			= 0x053,

	CAND_HMI1 							= 0x7C0,
	CAND_HMI2 							= 0x7D0,

} CAN_ADDR;

/* Exported struct ------------------------------------------------------------*/
typedef struct {
	CAN_TxHeaderTypeDef header;
	CAN_DATA data;
} can_tx_t;

typedef struct {
	CAN_RxHeaderTypeDef header;
	CAN_DATA data;
} can_rx_t;

typedef struct {
	uint8_t active;
	CAN_HandleTypeDef *pcan;
} can_t;

/* Public functions prototype ------------------------------------------------*/
void CANBUS_Init(void);
void CANBUS_DeInit(void);
uint8_t CANBUS_Filter(void);
uint8_t CANBUS_Write(can_tx_t *Tx, uint32_t address, uint32_t DLC, uint8_t ext);
uint8_t CANBUS_Read(can_rx_t *Rx);
uint32_t CANBUS_ReadID(CAN_RxHeaderTypeDef *RxHeader);

#endif /* CANBUS_H_ */
