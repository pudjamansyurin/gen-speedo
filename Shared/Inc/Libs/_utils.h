/*
 * _utils.h
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include "_defines.h"
#include "Drivers/_log.h"

/* Functions prototypes -------------------------------------------------------*/
void _DelayMS(uint32_t ms);
uint32_t _GetTickMS(void);
void _LedWrite(uint8_t state);
void _LedToggle(void);
void _Error(char msg[50]);
void _LcdBacklight(uint8_t state);
void _LcdPower(uint8_t state);
void _RightPad(char *dest, const char *src, const char pad, uint8_t sz);

#if (!BOOTLOADER)
void _FlushData(void);
float _D2R(uint16_t deg);
#else
uint32_t _ByteSwap32(uint32_t x);
#endif
#endif /* CONFIG_H_ */
