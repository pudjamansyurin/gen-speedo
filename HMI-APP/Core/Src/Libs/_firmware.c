/*
 * _firmware.c
 *
 *  Created on: 29 Jun 2020
 *      Author: geni
 */

/* Includes ------------------------------------------------------------------*/
#include "Libs/_firmware.h"
#include "Drivers/_canbus.h"

/* External variables ---------------------------------------------------------*/
extern canbus_t CB;
//extern uint16_t VCU_FW_VERSION;

/* Public functions implementation --------------------------------------------*/
void FW_EnterModeIAP(void) {
    /* Set flag to SRAM */
    *(uint32_t*) IAP_FLAG_ADDR = IAP_FLAG;
    //    *(uint32_t*) IAP_TYPE_ADDR = type;
    //    /* Retain VCU version */
    //    if (type == IAP_TYPE_VCU) {
    //        EEPROM_FirmwareVersion(EE_CMD_W, VCU_VERSION, IAP_TYPE_VCU);
    //    }
    /* Reset */
    HAL_NVIC_SystemReset();
}

uint8_t FW_UpgradeMe(void) {
    CAN_DATA *data = &(CB.rx.data);

    return (data->u32[0] == CAN_MY_ADRESS);
}
