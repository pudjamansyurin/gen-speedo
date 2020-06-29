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

/* Exported macro ------------------------------------------------------------*/
#define SRAM_SIZE               (uint32_t) 0x30000
#define SRAM_BASE_ADDR          (uint32_t) 0x20000000
#define SRAM_END_ADDR                      (SRAM_BASE_ADDR + SRAM_SIZE)

#define SP_MASK                 (uint32_t) 0x2FFFFFFF
#define SP_RANGE                           (SP_MASK - (SRAM_SIZE - 1))

//#define DFU_PROGRESS_FLAG       (uint32_t) 0x89ABCDEF
#define IAP_FLAG                (uint32_t) 0xAABBCCDD

#define IAP_FLAG_ADDR                      (SRAM_END_ADDR - sizeof(uint32_t))
//#define IAP_TYPE_ADDR                      (IAP_FLAG_ADDR - sizeof(uint32_t))

#define IS_VALID_SP(a)          ((*(__IO uint32_t*)a & SP_RANGE) == SRAM_BASE_ADDR)
//#define IS_DFU_IN_PROGRESS(v)   ((uint32_t)v == DFU_PROGRESS_FLAG)

/* Functions prototypes -------------------------------------------------------*/
void _DelayMS(uint32_t ms);
uint32_t _GetTickMS(void);
void _LedWrite(uint8_t state);
void _LedToggle(void);
void _SetBacklight(uint8_t state);

#if (!BOOTLOADER)
uint8_t _RTOS_ValidThreadFlag(uint32_t flag);
uint8_t _RTOS_ValidEventFlag(uint32_t flag);
void _FlushData(void);
float _D2R(uint16_t deg);
#endif
#endif /* CONFIG_H_ */
