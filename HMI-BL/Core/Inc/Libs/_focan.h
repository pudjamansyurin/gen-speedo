/*
 * _focan.h
 *
 *  Created on: 29 Jun 2020
 *      Author: geni
 */

#ifndef INC_LIBS__FOCAN_H_
#define INC_LIBS__FOCAN_H_

/* Includes ------------------------------------------------------------------*/
#include "Libs/_fota.h"

/* Exported macro -------------------------------------------------------------*/
#define BLK_SIZE                  (uint16_t) (256*5)
#define FOCAN_RETRY                (uint8_t) 1

/* Public functions implementation --------------------------------------------*/
uint8_t FOCAN_Upgrade(uint8_t update);
uint8_t FOCAN_RequestFota(void);
uint8_t FOCAN_xEnterModeIAP(void);
uint8_t FOCAN_xGetChecksum(void);
uint8_t FOCAN_xPraDownload(uint32_t *size);
uint8_t FOCAN_xPascaDownload(uint32_t *size);
uint8_t FOCAN_xDownloadFlash(uint32_t *size, uint32_t timeout, uint32_t *tick);

#endif /* INC_LIBS__FOCAN_H_ */
