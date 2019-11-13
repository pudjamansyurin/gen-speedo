/*
 * _config.c
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

#include "_config.h"

void BSP_Led_Write(uint8_t number, uint8_t state) {
	if (number == 1) {
		HAL_GPIO_WritePin(USE_HMI_LEFT ? LEFT_LD1_GPIO_Port : RIGHT_LD1_GPIO_Port,
				USE_HMI_LEFT ? LEFT_LD1_Pin : RIGHT_LD1_Pin, state);
	} else {
		HAL_GPIO_WritePin(USE_HMI_LEFT ? LEFT_LD2_GPIO_Port : RIGHT_LD2_GPIO_Port,
				USE_HMI_LEFT ? LEFT_LD2_Pin : RIGHT_LD2_Pin, state);
	}
}

void BSP_Led_Toggle(uint8_t number) {
	if (number == 1) {
		HAL_GPIO_TogglePin(USE_HMI_LEFT ? LEFT_LD1_GPIO_Port : RIGHT_LD1_GPIO_Port,
				USE_HMI_LEFT ? LEFT_LD1_Pin : RIGHT_LD1_Pin);
	} else {
		HAL_GPIO_TogglePin(USE_HMI_LEFT ? LEFT_LD2_GPIO_Port : RIGHT_LD2_GPIO_Port,
				USE_HMI_LEFT ? LEFT_LD2_Pin : RIGHT_LD2_Pin);
	}
}

void BSP_Set_Backlight(uint8_t state) {
	HAL_GPIO_WritePin(RIGHT_BACKLIGHT_GPIO_Port, RIGHT_BACKLIGHT_Pin, GPIO_PIN_SET);
}

float D2R(uint16_t deg) {
	return deg * M_PI / 180.0;
}
