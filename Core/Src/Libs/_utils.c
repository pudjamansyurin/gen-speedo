/*
 * _utils.c
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

/* Includes ------------------------------------------------------------------*/
#include "_utils.h"

/* External variables --------------------------------------------------------*/
extern display_t DISPLAY;

/* Functions -----------------------------------------------------------------*/
void _GUI_ClearRect(GUI_RECT *rect) {
	GUI_ClearRect(rect->x0, rect->y0, rect->x1, rect->y1);
}

void _GUI_IconMem(uint16_t x, uint16_t y, const GUI_BITMAP *fg, uint8_t show, uint8_t alpha) {
	// create & select MEMDEV
	GUI_SelectLayer(1);
	GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(x, y, x + fg->XSize, y + fg->XSize);
	GUI_MEMDEV_Select(hMem);

	// draw background
	_GUI_Icon(x, y, fg, show, alpha);

	// Print result & delete MEMDEV
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_CopyToLCD(hMem);
	GUI_MEMDEV_Delete(hMem);
}

void _GUI_Icon(uint16_t x, uint16_t y, const GUI_BITMAP *fg, uint8_t show, uint8_t alpha) {
	GUI_RECT pRect = { x, y, x + fg->XSize, y + fg->YSize };

	// draw background
	GUI_SetClipRect(&pRect);
	GUI_DrawBitmapEx(DISPLAY.background, x, y, x, y, 1000, 1000);
	GUI_SetClipRect(NULL);

	// draw indicator image
	if (show) {
		GUI_SetAlpha(alpha);
		GUI_DrawBitmap(fg, x, y);
		GUI_SetAlpha(255);
	}
}

void _LedWrite(uint8_t number, uint8_t state) {
	if (number == 1) {
		HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, state);
	} else {
		HAL_GPIO_WritePin(LD2_PORT, LD2_PIN, state);
	}
}

void _LedToggle(uint8_t number) {
	if (number == 1) {
		HAL_GPIO_TogglePin(LD1_PORT, LD1_PIN);
	} else {
		HAL_GPIO_TogglePin(LD2_PORT, LD2_PIN);
	}
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

float _D2R(uint16_t deg) {
	return deg * M_PI / 180.0;
}
