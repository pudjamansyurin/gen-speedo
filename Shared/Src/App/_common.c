/*
 * _common.c
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

/* Includes
 * --------------------------------------------*/
#include "App/_common.h"
#if (APP)
#include "Nodes/HMI1.h"
#include "Nodes/VCU.h"

#endif

/* Public functions implementations
 * --------------------------------------------*/
void _DelayMS(uint32_t ms) {
#if APP
  osDelay(ms);
#else
  HAL_Delay(ms);
#endif
}

uint32_t _GetTickMS(void) {
#if APP
  return osKernelGetTickCount();
#else
  return HAL_GetTick();
#endif
}

void _LedWrite(uint8_t state) {
  HAL_GPIO_WritePin(SYS_LED_GPIO_Port, SYS_LED_Pin, state);
}

void _LedToggle(void) { HAL_GPIO_TogglePin(SYS_LED_GPIO_Port, SYS_LED_Pin); }

void _Error(char msg[50]) {
#if APP
  if (osKernelGetState() == osKernelRunning) printf(msg);
#else
  printf(msg);
#endif

  //    // indicator error
  //    while (1) {
  //        _LedToggle();
  //        HAL_Delay(50);
  //    }
}

void _LcdBacklight(uint8_t state) {
  HAL_GPIO_WritePin(LCD_BACKLIGHT_GPIO_Port, LCD_BACKLIGHT_Pin, state);
}

void _LcdPower(uint8_t state) {
  HAL_GPIO_WritePin(LCD_POWER_GPIO_Port, LCD_POWER_Pin, state);
}

void _RightPad(char *dest, const char *src, const char pad, uint8_t sz) {
  memset(dest, pad, sz);
  memcpy(dest, src, strlen(src));
  dest[sz - 1] = 0x00;
}

float _D2R(uint16_t deg) { return deg * M_PI / 180.0; }

uint32_t _ByteSwap32(uint32_t x) {
  uint32_t y = (x >> 24) & 0xff;
  y |= ((x >> 16) & 0xff) << 8;
  y |= ((x >> 8) & 0xff) << 16;
  y |= (x & 0xff) << 24;

  return y;
}
