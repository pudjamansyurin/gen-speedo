/*
 * _utils.c
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

/* Includes ------------------------------------------------------------------*/
#include "Libs/_utils.h"
#if (!BOOTLOADER)
#include "Nodes/VCU.h"
#include "Nodes/HMI1.h"
#include "Nodes/MCU.h"
#include "Nodes/BMS.h"
#endif

/* Public functions implementations ------------------------------------------*/
#if RTOS_ENABLE
uint8_t _osThreadFlagsWait(uint32_t *notif, uint32_t flags, uint32_t options, uint32_t timeout) {
  *notif = osThreadFlagsWait(flags, options, timeout);

  return !(!(*notif) || ((*notif) & (~EVT_MASK)));
}
#endif

void _DelayMS(uint32_t ms) {
#if RTOS_ENABLE
    osDelay(ms);
#else
  HAL_Delay(ms);
#endif
}

uint32_t _GetTickMS(void) {
#if RTOS_ENABLE
    return osKernelGetTickCount();
#else
  return HAL_GetTick();
#endif
}

void _LedWrite(uint8_t state) {
	HAL_GPIO_WritePin(SYS_LED_GPIO_Port, SYS_LED_Pin, state);
}

void _LedToggle(void) {
	HAL_GPIO_TogglePin(SYS_LED_GPIO_Port, SYS_LED_Pin);
}

void _Error(char msg[50]) {
#if RTOS_ENABLE
    if (osKernelGetState() == osKernelRunning)
        Log(msg);
#else
	Log(msg);
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

#if (!BOOTLOADER)
void _FlushData(void) {
	VCU.Init();
	HMI1.Init();
	MCU.Init();
	BMS.Init();
	_LcdBacklight(1);
  Log("Data is flushed.\n");
}

float _D2R(uint16_t deg) {
	return deg * M_PI / 180.0;
}

#else
uint32_t _ByteSwap32(uint32_t x) {
    uint32_t y = (x >> 24) & 0xff;
    y |= ((x >> 16) & 0xff) << 8;
    y |= ((x >> 8) & 0xff) << 16;
    y |= (x & 0xff) << 24;

    return y;
}
#endif

