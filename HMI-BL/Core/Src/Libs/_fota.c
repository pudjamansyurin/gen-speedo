/*
 * _fota.c
 *
 *  Created on: 18 Jun 2020
 *      Author: geni
 */

/* Includes ------------------------------------------------------------------*/
#include "Libs/_fota.h"
#include "Libs/_focan.h"
#include "Drivers/_flasher.h"
#include "Drivers/_crc.h"
#include "BSP/_lcd.h"

/* External variables ---------------------------------------------------------*/
extern CAN_HandleTypeDef hcan2;
extern CRC_HandleTypeDef hcrc;

/* Public functions implementation --------------------------------------------*/
uint8_t FOTA_ValidateChecksum(uint32_t checksum, uint32_t len, uint32_t address) {
    uint8_t *addr = (uint8_t*) address;
    uint32_t crc = 0;

    // Calculate CRC
    crc = CRC_Calculate8(addr, len, 1);

    // Indicator
    LOG_Str("FOTA:Checksum = ");
    if (crc == checksum) {
        LOG_StrLn("MATCH");
        /* Glue checksum information to image */
        FOTA_GlueInfo32(CHECKSUM_OFFSET, &crc);
    } else {
        LOG_StrLn("NOT MATCH");
        LOG_Hex32(checksum);
        LOG_Str(" != ");
        LOG_Hex32(crc);
        LOG_Enter();
    }

    return (crc == checksum);
}

uint8_t FOTA_ValidImage(uint32_t address) {
    uint32_t size, checksum;
    uint8_t p;

    /* Check beginning stack pointer */
    p = IS_VALID_SP(APP_START_ADDR);

//    /* Check the size */
//    if (p) {
//        /* Get the stored size information */
//        size = *(uint32_t*) (address + SIZE_OFFSET);
//        p = (size < APP_MAX_SIZE );
//    }
//
//    /* Check the checksum */
//    if (p) {
//        /* Get the stored checksum information */
//        checksum = *(uint32_t*) (address + CHECKSUM_OFFSET);
//
//        /* Validate checksum */
//        p = FOTA_ValidateChecksum(checksum, size, address);
//    }

    return p;
}

void FOTA_JumpToApplication(void) {
    uint32_t appStack, appEntry;

    /* Get stack & entry pointer */
    appStack = *(__IO uint32_t*) APP_START_ADDR;
    appEntry = *(__IO uint32_t*) (APP_START_ADDR + 4);

    /* Shutdown all peripherals */
    HAL_CAN_MspDeInit(&hcan2);
    HAL_CRC_MspDeInit(&hcrc);
    BSP_LCD_DeInit();
    BSP_SDRAM_DeInit();
    HAL_RCC_DeInit();
    HAL_DeInit();

    /* Reset systick */
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;

    /* Set stack pointer */
    __set_MSP(appStack);

    /* Jump to user ResetHandler */
    void (*jump)(void) = (void (*)(void))(appEntry);
    jump();

    /* Never reached */
    while (1)
        ;
}

void FOTA_Reboot(void) {
    /* Clear backup area */
    FLASHER_EraseBkpArea();

    HAL_NVIC_SystemReset();
}

void FOTA_GetChecksum(uint32_t *checksum) {
    uint32_t address = BKP_START_ADDR;

    if (FOTA_NeedBackup()) {
        address = APP_START_ADDR;
    }

    *checksum = *(uint32_t*) (address + CHECKSUM_OFFSET);
}

void FOTA_GlueInfo32(uint32_t offset, uint32_t *data) {
    FLASHER_WriteAppArea((uint8_t*) data, sizeof(uint32_t), offset);
}

uint8_t FOTA_NeedBackup(void) {
    return (FOTA_ValidImage(APP_START_ADDR) && !FOTA_ValidImage(BKP_START_ADDR));
}

void FOTA_DisplayDevice(IAP_TYPE type) {
    char title[20];

    // decide the node
    strcpy(title, type == IAP_HMI ? "Device: HMI-1" : "Device: VCU");

    BSP_LCD_SetFont(&Font24);
    // clear
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(
            0,
            0,
            BSP_LCD_GetXSize() - 1,
            0 + Font24.Height);
    // set
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(
            0,
            0,
            (uint8_t*) title,
            LEFT_MODE);
}

void FOTA_DisplayStatus(char *status) {
    BSP_LCD_SetFont(&Font24);
    // clear
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(
            0,
            25,
            BSP_LCD_GetXSize() - 1,
            25 + Font24.Height);
    // set
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(
            0,
            25,
            (uint8_t*) status,
            LEFT_MODE);
}
void FOTA_DisplayPercent(uint8_t progress) {
    char percent[6];

    BSP_LCD_SetFont(&Font24);
    sprintf(percent, "%03d %%", progress);
    BSP_LCD_DisplayStringAt(
            (BSP_LCD_GetXSize() / 2) - 30,
            (BSP_LCD_GetYSize() / 2) - 10,
            (uint8_t*) percent,
            LEFT_MODE);
}
