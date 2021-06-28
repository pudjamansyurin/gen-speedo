/*
 * _fota.h
 *
 *  Created on: 18 Jun 2020
 *      Author: geni
 */

#ifndef INC_LIBS__FOTA_H_
#define INC_LIBS__FOTA_H_

/* Includes
 * --------------------------------------------*/
#include "App/_common.h"

/* Public functions prototype
 * --------------------------------------------*/
uint8_t FOTA_ValidateCRC(uint32_t crc, uint32_t len, uint32_t address);
uint8_t FOTA_ValidImage(uint32_t address);
void FOTA_JumpToApplication(void);
void FOTA_Reboot(void);
void FOTA_GetCRC(uint32_t *crc);
void FOTA_GlueInfo32(uint32_t offset, uint32_t *data);
uint8_t FOTA_NeedBackup(void);

void FOTA_DisplayDevice(IAP_TYPE type);
void FOTA_DisplayStatus(char *status);
void FOTA_DisplayPercent(float percent);
#endif /* INC_LIBS__FOTA_H_ */
