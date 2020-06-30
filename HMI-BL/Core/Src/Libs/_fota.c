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

/* External variables ---------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;
extern CRC_HandleTypeDef hcrc;

/* Public functions implementation --------------------------------------------*/
uint8_t FOTA_CompareChecksum(uint32_t checksum, uint32_t len, uint32_t address) {
    uint32_t crc = 0;
    uint8_t *addr = (uint8_t*) address;

    // Calculate CRC
    crc = CRC_Calculate8(addr, len, 1);

    // Indicator
    LOG_Str("FOTA:Checksum = ");
    if (crc == checksum) {
        LOG_StrLn("MATCH");
        /* Glue checksum information to image */
        FLASHER_WriteAppArea((uint8_t*) &crc, sizeof(uint32_t), CHECKSUM_OFFSET);
    } else {
        LOG_StrLn("NOT MATCH");
        LOG_Hex32(checksum);
        LOG_Str(" != ");
        LOG_Hex32(crc);
        LOG_Enter();
    }

    return (crc == checksum);
}

void FOTA_Reboot(void) {
    /* Clear backup area */
    FLASHER_EraseBkpArea();

    HAL_NVIC_SystemReset();
}

uint8_t FOTA_ValidImage(uint32_t address) {
    uint32_t size, checksum = 0, crc = 0;
    uint8_t ret;
    uint8_t *ptr = (uint8_t*) address;

    /* Check beginning stack pointer */
    ret = IS_VALID_SP(APP_START_ADDR);

    /* Check the size */
    if (ret) {
        /* Get the stored size information */
        size = *(uint32_t*) (address + SIZE_OFFSET);
        ret = (size < APP_MAX_SIZE );
    }

    /* Check the checksum */
    if (ret) {
        /* Get the stored checksum information */
        checksum = *(uint32_t*) (address + CHECKSUM_OFFSET);
        /* Calculate CRC */
        crc = CRC_Calculate8(ptr, size, 1);

        // Indicator
        LOG_Str("APP:Checksum = ");
        if (crc == checksum) {
            LOG_StrLn("MATCH");
        } else {
            LOG_StrLn("NOT MATCH");
            LOG_Hex32(checksum);
            LOG_Str(" != ");
            LOG_Hex32(crc);
            LOG_Enter();
        }

        ret = (checksum == crc);
    }

    return ret;
}

void FOTA_JumpToApplication(void) {
    uint32_t appStack, appEntry;

    /* Get stack & entry pointer */
    appStack = *(__IO uint32_t*) APP_START_ADDR;
    appEntry = *(__IO uint32_t*) (APP_START_ADDR + 4);

    /* Shutdown all peripherals */
    HAL_CAN_MspDeInit(&hcan1);
    HAL_CRC_MspDeInit(&hcrc);
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

uint8_t FOTA_Upgrade(void) {
    uint8_t p;
    uint32_t checksum;

    // Backup current application
    if (FOTA_NeedBackup()) {
        FLASHER_BackupApp();
    }

    /* Upgrade */
    /* Get the stored checksum information */
    checksum = *(uint32_t*) (BKP_START_ADDR + CHECKSUM_OFFSET);
    /* Download image and install */
    p = Simcom_FOTA(checksum);

    return p;
}

uint8_t FOTA_NeedBackup(void) {
    return (FOTA_ValidImage(APP_START_ADDR) && !FOTA_ValidImage(BKP_START_ADDR));
}
