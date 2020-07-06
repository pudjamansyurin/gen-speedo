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
#define BLK_SIZE                        0xFF

/* Public functions implementation --------------------------------------------*/
uint8_t FOCAN_Update(void);
uint8_t FOCAN_xEnterModeIAP(void);
uint8_t FOCAN_xGetChecksum(uint32_t *checksum);
uint8_t FOCAN_xPraDownload(uint32_t *size);
uint8_t FOCAN_xPascaDownload(uint32_t *size);
uint8_t FOCAN_xDownloadFlash(uint32_t timeout);

#endif /* INC_LIBS__FOCAN_H_ */
