/*
 * _fota.h
 *
 *  Created on: 18 Jun 2020
 *      Author: geni
 */

#ifndef INC_LIBS__FOTA_H_
#define INC_LIBS__FOTA_H_

/* Includes ------------------------------------------------------------------*/
#include "Libs/_utils.h"

/* Public functions implementation --------------------------------------------*/
//uint8_t FOTA_Upgrade(void);
uint8_t FOTA_ValidateChecksum(uint32_t checksum, uint32_t len, uint32_t address);
uint8_t FOTA_ValidImage(uint32_t address);
void FOTA_JumpToApplication(void);
void FOTA_Reboot(void);
void FOTA_GetChecksum(uint32_t *checksum);
void FOTA_GlueInfo32(uint32_t offset, uint32_t *data);
uint8_t FOTA_NeedBackup(void);

#endif /* INC_LIBS__FOTA_H_ */
