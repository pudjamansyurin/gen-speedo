/*
 * _database.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Pudja Mansyurin
 */

#ifndef DEFINES_H_
#define DEFINES_H_

/* Choose between VCU or Boot-loader mode */
#define APP 0

/* Includes
 * --------------------------------------------*/
#include "_defs_shared.h"

#define CAN_DEBUG 0

/* Exported enums
 * --------------------------------------------*/
typedef enum { IAP_VCU = 0xA1B2C3D4, IAP_HMI = 0x1A2B3C4D } IAP_TYPE;

typedef enum { FOCAN_ERROR = 0x00, FOCAN_ACK = 0x79, FOCAN_NACK = 0x1F } FOCAN;

#endif /* DEFINES_H_ */
