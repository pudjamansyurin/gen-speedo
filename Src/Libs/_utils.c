/*
 * _utils.c
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

#include "_utils.h"

void BSP_Led_Write(uint8_t number, uint8_t state) {
	if (number == 1) {
		HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, state);
	} else {
		HAL_GPIO_WritePin(LD2_PORT, LD2_PIN, state);
	}
}

void BSP_Led_Toggle(uint8_t number) {
	if (number == 1) {
		HAL_GPIO_TogglePin(LD1_PORT, LD1_PIN);
	} else {
		HAL_GPIO_TogglePin(LD2_PORT, LD2_PIN);
	}
}

void BSP_Set_Backlight(uint8_t state) {
	HAL_GPIO_WritePin(RIGHT_BACKLIGHT_GPIO_Port, RIGHT_BACKLIGHT_Pin, state);
}

float D2R(uint16_t deg) {
	return deg * M_PI / 180.0;
}
