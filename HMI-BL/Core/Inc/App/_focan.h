/*
 * _focan.h
 *
 *  Created on: 29 Jun 2020
 *      Author: geni
 */

#ifndef INC_LIBS__FOCAN_H_
#define INC_LIBS__FOCAN_H_

/* Includes
 * --------------------------------------------*/
#include "App/_fota.h"
#include "Drivers/_canbus.h"

/* Exported constants
 * --------------------------------------------*/
#define BLK_SIZE (uint16_t)(256 * 5)
#define FOCAN_RETRY (uint8_t)1

/* Public functions prototype
 * --------------------------------------------*/
uint8_t FOCAN_Upgrade(uint8_t factory);
uint8_t FOCAN_RequestFota(void);
uint8_t FOCAN_xGetCRC(void);
uint8_t FOCAN_xSetProgress(can_rx_t *Rx, IAP_TYPE *type);
uint8_t FOCAN_xPraDownload(can_rx_t *Rx, uint32_t *size);
uint8_t FOCAN_xPascaDownload(can_rx_t *Rx, uint32_t *size);
uint8_t FOCAN_xDownloadFlash(can_rx_t *Rx, uint32_t *size, uint32_t timeout,
                             uint32_t *tick);

#endif /* INC_LIBS__FOCAN_H_ */
