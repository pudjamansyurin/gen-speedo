/*
 * BMS.h
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

#ifndef INC_NODES_BMS_H_
#define INC_NODES_BMS_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "_defines.h"

/* Exported struct --------------------------------------------------------------*/
typedef struct {
	uint8_t soc;
} bms_data_t;

typedef struct {
	bms_data_t d;
	void (*Init)(void);
} bms_t;

/* Public functions implementation --------------------------------------------*/
void BMS_Init(void);

#endif /* INC_NODES_BMS_H_ */
