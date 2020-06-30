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
uint8_t FOTA_CompareChecksum(uint32_t checksum, uint32_t len, uint32_t address);
void FOTA_Reboot(void);
uint8_t FOTA_ValidImage(uint32_t address);
uint8_t FOTA_InProgressDFU(void);
void FOTA_JumpToApplication(void);
uint8_t FOTA_Upgrade(void);
uint8_t FOTA_NeedBackup(void);

#endif /* INC_LIBS__FOTA_H_ */
