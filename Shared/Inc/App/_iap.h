/*
 * _iap.h
 *
 *  Created on: Jun 28, 2021
 *      Author: pudja
 */

#ifndef INC_APP__IAP_H_
#define INC_APP__IAP_H_

/* Includes
 * --------------------------------------------*/
#include "_defs.h"

/* Exported defines
 * --------------------------------------------*/
/* SRAM related */
#define SRAM_SIZE ((uint32_t)0x30000)
#define SRAM_BASE_ADDR ((uint32_t)0x20000000)
#define SRAM_END_ADDR (SRAM_BASE_ADDR + SRAM_SIZE)
#define SP_MASK ((uint32_t)0x2FFFFFFF)
#define SP_RANGE (SP_MASK - (SRAM_SIZE - 1))

#define IAP_FLAG_ADDR (SRAM_END_ADDR - 4)
#define IS_VALID_SP(a) ((*(__IO uint32_t *)a & SP_RANGE) == SRAM_BASE_ADDR)

/* FLASH related */
/* APP Firmware */
#define APP_MAX_SIZE ((uint32_t)0xE0000)
#define APP_START_ADDR ((uint32_t)0x08020000)
#define APP_END_ADDR (APP_START_ADDR + APP_MAX_SIZE - 1)
#define BKP_START_ADDR ((uint32_t)0x08120000)
#define BKP_END_ADDR (BKP_START_ADDR + APP_MAX_SIZE - 1)
#define SIZE_OFFSET (APP_MAX_SIZE - 4)
#define CRC_OFFSET (APP_MAX_SIZE - 8)
/* Bootloader */
#define BL_MAX_SIZE ((uint32_t)0x10000)
#define BL_START_ADDR ((uint32_t)0x08000000)
#define BL_END_ADDR (BL_START_ADDR + BL_MAX_SIZE - 1)
#define HIN_VALUE (*(__IO uint32_t *)(BL_MAX_SIZE - 4))

/* Exported enums
 * --------------------------------------------*/
typedef enum {
	FOCAN_ERROR = 0x00,
	FOCAN_ACK = 0x79,
	FOCAN_NACK = 0x1F
} FOCAN;


typedef enum {
	ITYPE_VCU = 0xA1B2C3D4,
	ITYPE_HMI = 0x1A2B3C4D
} IAP_TYPE;

typedef enum {
  IFLAG_RESET = 0,
  IFLAG_SRAM = 0xAABBCCDD,
} IAP_FLAG;

#endif /* INC_APP__IAP_H_ */
