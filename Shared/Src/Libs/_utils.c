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

/* External variables --------------------------------------------------------*/
extern vcu_t VCU;
extern hmi1_t HMI1;
extern mcu_t MCU;
extern bms_t BMS;
#endif

/* Functions -----------------------------------------------------------------*/
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
    HAL_GPIO_WritePin(LD1_PORT, LD1_PIN, state);
    HAL_GPIO_WritePin(LD2_PORT, LD2_PIN, state);
}

void _LedToggle(void) {
    HAL_GPIO_TogglePin(LD1_PORT, LD1_PIN);
    HAL_GPIO_TogglePin(LD2_PORT, LD2_PIN);
}

void _Error(char msg[50]) {
#if RTOS_ENABLE
    if (osKernelGetState() == osKernelRunning) {
        LOG_StrLn(msg);
    }
#else
    LOG_StrLn(msg);
#endif

    // indicator error
    while (1) {
        _LedToggle();
        HAL_Delay(50);
    }
}

void _SetBacklight(uint8_t state) {
#if !USE_HMI_LEFT
    HAL_GPIO_WritePin(RIGHT_BACKLIGHT_GPIO_Port, RIGHT_BACKLIGHT_Pin, state);
#endif
}

#if (!BOOTLOADER)
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

void _FlushData(void) {
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
#else
uint32_t _ByteSwap32(uint32_t x) {
    uint32_t y = (x >> 24) & 0xff;
    y |= ((x >> 16) & 0xff) << 8;
    y |= ((x >> 8) & 0xff) << 16;
    y |= (x & 0xff) << 24;

    return y;
}
#endif

