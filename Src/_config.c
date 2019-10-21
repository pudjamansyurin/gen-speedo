/*
 * _config.c
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

#include "_config.h"

void BSP_Led_Write(uint8_t number, uint8_t state) {
	if (number == 1) {
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, state);
	} else {
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, state);
	}
}

void BSP_Led_Toggle(uint8_t number) {
	if (number == 1) {
		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	} else {
		HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
	}
}
