/*
 * MCU.h
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

#ifndef INC_NODES_MCU_H_
#define INC_NODES_MCU_H_

/* Includes ------------------------------------------------------------------*/
#include "Libs/_utils.h"

/* Exported struct -----------------------------------------------------------*/
typedef struct {
	uint32_t rpm;
	uint32_t temperature;
} mcu_data_t;

typedef struct {
	mcu_data_t d;
	void (*Init)(void);
} mcu_t;

/* Public functions implementation --------------------------------------------*/
void MCU_Init(void);

#endif /* INC_NODES_MCU_H_ */
