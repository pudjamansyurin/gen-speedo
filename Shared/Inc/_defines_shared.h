/*
 * _database.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */

#ifndef DEFINES_SHARED_H_
#define DEFINES_SHARED_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#if (!BOOTLOADER)
#include "cmsis_os.h"
#endif

/* Exported constants --------------------------------------------------------*/
#define RTOS_ENABLE                             !BOOTLOADER

// macro to manipulate bit
#define BIT(x)                              (1ULL << x)
#define BV(var, x)                          (var |= (1ULL << x))
#define BC(var, x)                          (var &= ~(1ULL << x))
#define BT(var, x)                          (var ^= (1ULL << x))

/* SRAM related */
#define SRAM_SIZE                    (uint32_t) 0x30000
#define SRAM_BASE_ADDR               (uint32_t) 0x20000000
#define SRAM_END_ADDR                           (SRAM_BASE_ADDR + SRAM_SIZE)
#define SP_MASK                      (uint32_t) 0x2FFFFFFF
#define SP_RANGE                                (SP_MASK - (SRAM_SIZE - 1))

#define IAP_FLAG                     (uint32_t) 0xAABBCCDD
#define IAP_FLAG_ADDR                           (SRAM_END_ADDR - 4)
#define IS_VALID_SP(a)               ((*(__IO uint32_t*)a & SP_RANGE) == SRAM_BASE_ADDR)

/* FLASH related */
#define APP_MAX_SIZE                 (uint32_t) 0xE0000
#define APP_START_ADDR               (uint32_t) 0x08020000
#define APP_END_ADDR                            (APP_START_ADDR + APP_MAX_SIZE - 1)
#define BKP_START_ADDR               (uint32_t) 0x08120000
#define BKP_END_ADDR                            (BKP_START_ADDR + APP_MAX_SIZE - 1)
#define SIZE_OFFSET                             (APP_MAX_SIZE - 4)
#define CHECKSUM_OFFSET                         (APP_MAX_SIZE - 8)

#endif /* DEFINES_SHARED_H_ */
