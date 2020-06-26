/*
 * _utils.c
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

/* Includes ------------------------------------------------------------------*/
#include "Libs/_utils.h"
#include "Nodes/VCU.h"
#include "Nodes/HMI1.h"
#include "Nodes/MCU.h"
#include "Nodes/BMS.h"

/* External variables --------------------------------------------------------*/
extern vcu_t VCU;
extern hmi1_t HMI1;
extern mcu_t MCU;
extern bms_t BMS;

/* Functions -----------------------------------------------------------------*/
void _LedWrite(uint8_t state) {
	HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, state);
	HAL_GPIO_WritePin(LD2_PORT, LD2_PIN, state);
}

void _LedToggle(void) {
	HAL_GPIO_TogglePin(LD1_PORT, LD1_PIN);
	HAL_GPIO_TogglePin(LD2_PORT, LD2_PIN);
}

uint8_t _RTOS_ValidThreadFlag(uint32_t flag) {
	uint8_t ret = 1;

	// check is empty
	if (!flag) {
		ret = 0;
	} else if (flag & (~EVT_MASK)) {
		// error
		ret = 0;
	}

	return ret;
}

uint8_t _RTOS_ValidEventFlag(uint32_t flag) {
	uint8_t ret = 1;

	// check is empty
	if (!flag) {
		ret = 0;
	} else if (flag & (~EVENT_MASK)) {
		// error
		ret = 0;
	}

	return ret;
}

void _SetBacklight(uint8_t state) {
#if !USE_HMI_LEFT
	HAL_GPIO_WritePin(RIGHT_BACKLIGHT_GPIO_Port, RIGHT_BACKLIGHT_Pin, state);
#endif
}

void _ResetSystem(void) {
	VCU.Init();
	HMI1.Init();
	MCU.Init();
	BMS.Init();

	// default backlight is ON
	_SetBacklight(1);
}

float _D2R(uint16_t deg) {
	return deg * M_PI / 180.0;
}
