/*
 * _focan.c
 *
 *  Created on: 29 Jun 2020
 *      Author: geni
 */

/* Includes ------------------------------------------------------------------*/
#include "Libs/_focan.h"
#include "Drivers/_flasher.h"
#include "Drivers/_canbus.h"
#include "BSP/_lcd.h"

/* External variables ---------------------------------------------------------*/
extern IWDG_HandleTypeDef hiwdg;

/* Private functions prototypes -----------------------------------------------*/
static uint8_t FOCAN_SendResponse(uint32_t address, FOCAN response);
static uint8_t FOCAN_SendSqueeze(uint32_t address, void *data, uint8_t size);

/* Public functions implementation --------------------------------------------*/
uint8_t FOCAN_Upgrade(uint8_t factory) {
  can_rx_t Rx;
  uint8_t p = 1, success = 0;
  uint32_t timeout = 30000;
  uint32_t tick, iTick;
  uint32_t SIZE = 0;
  IAP_TYPE type = IAP_HMI;

  // Empty Firmware
  if (factory) {
    FOTA_DisplayDevice(IAP_HMI);
    FOTA_DisplayStatus("No Firmware.");
    FOCAN_RequestFota();
  }

  // Wait command
  tick = _GetTickMS();
  iTick = tick;
  do {
    // read
    if (CANBUS_Read(&Rx)) {
      switch (CANBUS_ReadID(&(Rx.header))) {
        case CAND_FOCAN_CRC :
          tick = _GetTickMS();
          p = FOCAN_xGetCRC();
          break;
        case CAND_FOCAN_PRA :
          tick = _GetTickMS();
          FOTA_DisplayStatus("Pra-Download.");
          p = FOCAN_xPraDownload(&Rx, &SIZE);
          break;
        case CAND_FOCAN_INIT :
          tick = _GetTickMS();
          p = SIZE;
          if (p)
            p = FOCAN_xDownloadFlash(&Rx, &SIZE, timeout, &tick);

          break;
        case CAND_FOCAN_PASCA :
          tick = _GetTickMS();
          FOTA_DisplayStatus("Pasca-Download");
          p = SIZE;
          if (p)
            p = FOCAN_xPascaDownload(&Rx, &SIZE);

          /* Handle success DFU */
          success = p;
          break;
        case CAND_FOCAN_PROGRESS :
          tick = _GetTickMS();
          FOCAN_xSetProgress(&Rx, &type);
          break;
        case CAND_VCU_SWITCH :
          if (factory)
            FOCAN_RequestFota();
          else
            p = 0;

          break;
        default:
          break;
      }
    }

    // indicator
    if ((_GetTickMS() - iTick) > 100) {
      iTick = _GetTickMS();
      _LedToggle();
    }

    // handle timeout
    if (_GetTickMS() - tick > timeout)
      p = 0;

    // reset watchdog
    HAL_IWDG_Refresh(&hiwdg);
  } while (p && !success);

  // Final response
  if (type == IAP_HMI) {
    if (success)
      FOTA_DisplayStatus("Success.");
    else
      FOTA_DisplayStatus("Failed.");
    _DelayMS(1000);
  }

  return p;
}

uint8_t FOCAN_RequestFota(void) {
	can_tx_t Tx = {0};

  Tx.data.u16[0] = 0xFFFF;
  
  return CANBUS_Write(&Tx, CAND_HMI1, 2, 0);
}

uint8_t FOCAN_xGetCRC(void) {
  uint32_t address = CAND_FOCAN_CRC;
  uint32_t crc;

  // Make message
  FOTA_GetCRC(&crc);

  // Send response
  return FOCAN_SendSqueeze(address, &crc, 4);
}

uint8_t FOCAN_xSetProgress(can_rx_t *Rx, IAP_TYPE *type) {
  uint8_t p;
  float percent;

  // Get
  *type = Rx->data.u32[0];
  percent = Rx->data.FLOAT[1];

  // Handle
  FOTA_DisplayDevice(*type);
  FOTA_DisplayStatus(percent > 0.0f ? "Downloading..." : "Connecting...");
  FOTA_DisplayPercent(percent);

  // Send response
  p = 1;

  return p;
}

uint8_t FOCAN_xPraDownload(can_rx_t *Rx, uint32_t *size) {
  uint32_t address = CAND_FOCAN_PRA;
  uint8_t p;

  // Read
  *size = Rx->data.u32[0];

  // Execute
  p = FLASHER_BackupApp();

  // Send response
  FOCAN_SendResponse(address, p ? FOCAN_ACK : FOCAN_NACK);

  return p;
}

uint8_t FOCAN_xDownloadFlash(can_rx_t *Rx, uint32_t *size, uint32_t timeout, uint32_t *tick) {
  uint32_t offset, currentSize, address;
  uint8_t p, percent, len = 0, ptr[BLK_SIZE ];
  uint16_t pos = 0;

  // read
  offset = Rx->data.u32[0];
  currentSize = Rx->data.u16[2] + 1;

  // check the flash size
  p = (offset + currentSize) <= APP_MAX_SIZE;
  // Send response
  FOCAN_SendResponse(CAND_FOCAN_INIT, p ? FOCAN_ACK : FOCAN_NACK);

  // Wait data
  if (p) {
    *tick = _GetTickMS();
    do {
      // read
      if (CANBUS_Read(Rx)) {
        if ((CANBUS_ReadID(&(Rx->header)) >> 20) == CAND_FOCAN_RUNNING) {
          pos = (CANBUS_ReadID(&(Rx->header)) & 0xFFFF);

          // read
          len = Rx->header.DLC;
          memcpy(&ptr[pos], &(Rx->data), len);

          // response ACK
          address = (CAND_FOCAN_RUNNING << 20) | pos;
          p = FOCAN_SendResponse(address, FOCAN_ACK);

          // update tick
          *tick = _GetTickMS();
          _LedToggle();
        }
      }
      // handle timeout
      if ((_GetTickMS() - *tick > timeout))
        p = 0;

    } while (p && ((pos + len) < currentSize));
  }

  // validate received size
  if (p)
    p = ((pos + len) == currentSize);

  // flash to firmware
  if (p)
    p = FLASHER_WriteAppArea(ptr, currentSize, offset);

  // progress indicator
  if (p) {
    percent = offset * 100 / *size;
    printf("FOTA:Progress = %lu Bytes (%u%%)\n", offset, percent);
  }

  // send final response
  FOCAN_SendResponse(CAND_FOCAN_INIT, p ? FOCAN_ACK : FOCAN_NACK);

  return p;
}

uint8_t FOCAN_xPascaDownload(can_rx_t *Rx, uint32_t *size) {
  uint32_t address = CAND_FOCAN_PASCA;
  uint32_t crc;
  uint8_t p;

  // Read
  crc = Rx->data.u32[0];

  // Execute
  p = FOTA_ValidateCRC(crc, *size, APP_START_ADDR);
  // Glue related information to new image
  if (p) {
    FOTA_GlueInfo32(CRC_OFFSET, &crc);
    FOTA_GlueInfo32(SIZE_OFFSET, size);
  }

  // Send response
  FOCAN_SendResponse(address, p ? FOCAN_ACK : FOCAN_NACK);

  return p;
}

/* Private functions implementation ------------------------------------------*/
static uint8_t FOCAN_SendSqueeze(uint32_t address, void *data, uint8_t size) {
	can_tx_t Tx = {0};
  uint8_t retry = FOCAN_RETRY, p;

  do {
    // ack
    p = FOCAN_SendResponse(address, FOCAN_ACK);
    // version
    if (p) {
      // set message
      memcpy(&(Tx.data), data, size);
      // send message
      p = CANBUS_Write(&Tx, address, size, 0);
    }
    // ack
    if (p)
      p = FOCAN_SendResponse(address, FOCAN_ACK);

  } while (!p && --retry);

  return p;
}

static uint8_t FOCAN_SendResponse(uint32_t address, FOCAN response) {
	can_tx_t Tx = {0};
  uint8_t retry = FOCAN_RETRY, p;

  do {
    // set message
    Tx.data.u8[0] = response;
    // send message
    p = CANBUS_Write(&Tx, address, 1, 0);
  } while (!p && --retry);

  return p;
}
