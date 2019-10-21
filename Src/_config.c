/*
 * _config.c
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

#include "_config.h"

void BSP_Led_Write(uint8_t number, uint8_t state) {
	if (number == 1) {
		HAL_GPIO_WritePin(LEFT_LD1_GPIO_Port, LEFT_LD1_Pin, state);
	} else {
		HAL_GPIO_WritePin(LEFT_LD2_GPIO_Port, LEFT_LD2_Pin, state);
	}
}

void BSP_Led_Toggle(uint8_t number) {
	if (number == 1) {
		HAL_GPIO_TogglePin(LEFT_LD1_GPIO_Port, LEFT_LD1_Pin);
	} else {
		HAL_GPIO_TogglePin(LEFT_LD2_GPIO_Port, LEFT_LD2_Pin);
	}
}
