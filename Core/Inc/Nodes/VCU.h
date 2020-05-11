/*
 * VCU.h
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

#ifndef INC_NODES_VCU_H_
#define INC_NODES_VCU_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported struct --------------------------------------------------------------*/
typedef struct {
	uint8_t signal;
	uint8_t speed;
	uint32_t odometer;
} vcu_data_t;

typedef struct {
	struct {
		void (*Switch)(void);
		void (*SelectSet)(void);
		void (*TripMode)(void);
	} r;
} vcu_can_t;

typedef struct {
	vcu_data_t d;
	vcu_can_t can;
	void (*Init)(void);
} vcu_t;

/* Public functions implementation --------------------------------------------*/
void VCU_Init(void);
void VCU_CAN_RX_Switch(void);
void VCU_CAN_RX_SelectSet(void);
void VCU_CAN_RX_TripMode(void);

#endif /* INC_NODES_VCU_H_ */
