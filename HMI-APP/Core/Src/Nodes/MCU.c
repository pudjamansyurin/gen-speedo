/*
 * MCU.c
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

/* Includes ------------------------------------------------------------------*/
#include "Nodes/MCU.h"

/* Public variables -----------------------------------------------------------*/
mcu_t MCU = {
		.d = { 0 },
		MCU_Init
};

/* Public functions implementation --------------------------------------------*/
void MCU_Init(void) {
	MCU.d.rpm = 0;
	MCU.d.temperature = 0;
}

