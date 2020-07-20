/*
 * _firmware.c
 *
 *  Created on: 29 Jun 2020
 *      Author: geni
 */

/* Includes ------------------------------------------------------------------*/
#include "Libs/_firmware.h"
#include "Drivers/_canbus.h"

/* Public functions implementation --------------------------------------------*/
void FW_EnterModeIAP(void) {
    /* Set flag to SRAM */
    *(uint32_t*) IAP_FLAG_ADDR = IAP_FLAG;
    /* Reset */
    HAL_NVIC_SystemReset();
}
