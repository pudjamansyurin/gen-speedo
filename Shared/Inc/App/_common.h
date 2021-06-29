/*
 * _common.h
 *
 *  Created on: Aug 26, 2019
 *      Author: Pudja Mansyurin
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/* Includes
 * --------------------------------------------*/
#include "_defs.h"
#include "Drivers/_log.h"
#include "App/_iap.h"

#if APP
#include "Libs/_rtos.h"
#endif

/* Exported macros
 * --------------------------------------------*/
#define BIT(x) (1ULL << x)
#define BV(var, x) (var |= (1ULL << x))
#define BC(var, x) (var &= ~(1ULL << x))
#define BT(var, x) (var ^= (1ULL << x))

/* Exported unions
 * --------------------------------------------*/
typedef union {
  uint8_t u8[8];
  uint16_t u16[4];
  uint32_t u32[2];
  uint64_t u64;
  int8_t s8[8];
  int16_t s16[4];
  int32_t s32[2];
  int64_t s64;
  char CHAR[8];
  float FLOAT[2];
  double DOUBLE;
} UNION64;

/* Public functions prototypes
 * --------------------------------------------*/
void _DelayMS(uint32_t ms);
uint32_t _GetTickMS(void);
void _LedWrite(uint8_t state);
void _LedToggle(void);
void _Error(char msg[50]);
void _LcdBacklight(uint8_t state);
void _LcdPower(uint8_t state);
void _RightPad(char *dest, const char *src, const char pad, uint8_t sz);
float _D2R(uint16_t deg);
uint32_t _ByteSwap32(uint32_t x);
#endif /* CONFIG_H_ */
