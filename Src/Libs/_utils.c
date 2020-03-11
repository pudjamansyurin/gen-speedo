/*
 * _utils.c
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

#include "_utils.h"

void _Indicator(const GUI_BITMAP *bg, const GUI_BITMAP *fg, uint16_t x, uint16_t y, uint8_t status, uint8_t alpha) {
  GUI_RECT pRect = { x, y, x + fg->XSize, y + fg->YSize };

  // draw background
  GUI_SetClipRect(&pRect);
  GUI_DrawBitmapEx(bg, x, y, x, y, 1000, 1000);
  GUI_SetClipRect(NULL);

  // draw indicator image
  if (status == 1) {
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

void _SetBacklight(uint8_t state) {
#if !USE_HMI_LEFT
	HAL_GPIO_WritePin(RIGHT_BACKLIGHT_GPIO_Port, RIGHT_BACKLIGHT_Pin, state);
#endif
}

float _D2R(uint16_t deg) {
  return deg * M_PI / 180.0;
}
