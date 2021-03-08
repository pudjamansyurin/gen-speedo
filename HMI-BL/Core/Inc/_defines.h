/*
 * _database.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */

#ifndef DEFINES_H_
#define DEFINES_H_

/* Choose between VCU or Boot-loader mode */
#define BOOTLOADER                          1

/* Includes ------------------------------------------------------------------*/
#include "_defines_shared.h"

/* Enum prototypes ------------------------------------------------------- */
typedef enum {
    IAP_VCU = 0xA1B2C3D4,
    IAP_HMI = 0x1A2B3C4D
} IAP_TYPE;

typedef enum {
    FOCAN_ERROR = 0x00,
    FOCAN_ACK = 0x79,
    FOCAN_NACK = 0x1F
} FOCAN;

#endif /* DEFINES_H_ */
