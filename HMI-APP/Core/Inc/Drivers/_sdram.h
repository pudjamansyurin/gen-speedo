/*
 * _sdram.h
 *
 *  Created on: Mar 13, 2020
 *      Author: pudja
 */

#ifndef INC_DRIVERS__SDRAM_H_
#define INC_DRIVERS__SDRAM_H_

/* Includes
 * --------------------------------------------*/
#include "App/_common.h"

/* Exported constants
 * --------------------------------------------*/
#define REFRESH_COUNT ((uint32_t)1386)
#define SDRAM_TIMEOUT ((uint32_t)0xFFFF)
#define SDRAM_MODEREG_BURST_LENGTH_1 ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2 ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4 ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8 ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2 ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3 ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE ((uint16_t)0x0200)

/* Public functions prototype
 * --------------------------------------------*/
void MX_SDRAM_InitEx(void);
void MX_SDRAM_DeInitEx(void);

#endif /* INC_DRIVERS__SDRAM_H_ */
