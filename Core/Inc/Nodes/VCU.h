/*
 * VCU.h
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

#ifndef INC_NODES_VCU_H_
#define INC_NODES_VCU_H_

/* Includes ------------------------------------------------------------------*/
#include "Libs/_utils.h"

/* Exported struct -----------------------------------------------------------*/
typedef struct {
	uint8_t signal;
	uint8_t speed;
	uint32_t odometer;
} vcu_data_t;

typedef struct {
	struct {
		void (*SwitchModeControl)(void);
		void (*MixedData)(void);
		void (*SubTripData)(void);
	} r;
} vcu_can_t;

typedef struct {
	vcu_data_t d;
	vcu_can_t can;
	void (*Init)(void);
} vcu_t;

/* Public functions implementation --------------------------------------------*/
void VCU_Init(void);
void VCU_CAN_RX_SwitchModeControl(void);
void VCU_CAN_RX_MixedData(void);
void VCU_CAN_RX_SubTripData(void);

#endif /* INC_NODES_VCU_H_ */
