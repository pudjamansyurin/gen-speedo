/*
 * _focan.c
 *
 *  Created on: 29 Jun 2020
 *      Author: Pudja Mansyurin
 */

/* Includes
 * --------------------------------------------*/
#include "App/_focan.h"

#include "BSP/_lcd.h"
#include "Drivers/_canbus.h"
#include "Drivers/_flasher.h"

/* External variables
 * --------------------------------------------*/
extern IWDG_HandleTypeDef hiwdg;

/* Private functions prototypes
 * --------------------------------------------*/
static uint8_t SendResponse(uint32_t address, uint8_t response);
static uint8_t SendSqueeze(uint32_t address, void *data, uint8_t size);

/* Public functions implementation
 * --------------------------------------------*/
uint8_t FOCAN_Upgrade(uint8_t factory) {
  can_rx_t Rx = {0};
  uint8_t p = 1, ok = 0;
  uint32_t tick, iTick, timeout = 30000, SIZE = 0;
  IAP_TYPE type = ITYPE_HMI;

  // Empty Firmware
  if (factory) {
    FOTA_DisplayDevice(ITYPE_HMI);
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
        case CAND_FOCAN_CRC:
          tick = _GetTickMS();
          p = FOCAN_xGetCRC();
          break;
        case CAND_FOCAN_PRA:
          tick = _GetTickMS();
          FOTA_DisplayStatus("Pra-Download.");
          p = FOCAN_xPraDownload(&Rx, &SIZE);
          break;
        case CAND_FOCAN_INIT:
          tick = _GetTickMS();
          p = SIZE;
          if (p) p = FOCAN_xDownloadFlash(&Rx, &SIZE, timeout, &tick);

          break;
        case CAND_FOCAN_PASCA:
          tick = _GetTickMS();
          FOTA_DisplayStatus("Pasca-Download");
          p = SIZE;
          if (p) p = FOCAN_xPascaDownload(&Rx, &SIZE);

          /* Handle success IAP */
          ok = p;
          break;
        case CAND_FOCAN_PROGRESS:
          tick = _GetTickMS();
          FOCAN_xSetProgress(&Rx, &type);
          break;
        case CAND_VCU_SWITCH_CTL:
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
    if (_GetTickMS() - tick > timeout) p = 0;

    // reset watchdog
    HAL_IWDG_Refresh(&hiwdg);
  } while (p && !ok);

  // Final response
  if (type == ITYPE_HMI) {
    FOTA_DisplayStatus(ok ? "Success." : "Failed.");
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
  uint32_t crc;

  // Make message
  FOTA_GetCRC(&crc);

  // Send response
  return SendSqueeze(CAND_FOCAN_CRC, &crc, 4);
}

uint8_t FOCAN_xSetProgress(can_rx_t *Rx, IAP_TYPE *type) {
  float percent;

  // Get
  *type = Rx->data.u32[0];
  percent = Rx->data.FLOAT[1];

  // Handle
  FOTA_DisplayDevice(*type);
  FOTA_DisplayStatus(percent > 0.0f ? "Downloading..." : "Connecting...");
  FOTA_DisplayPercent(percent);

  return 1;
}

uint8_t FOCAN_xPraDownload(can_rx_t *Rx, uint32_t *size) {
  uint8_t p;

  // Read
  *size = Rx->data.u32[0];

  // Execute
  p = FLASHER_BackupApp();

  // Send response
  SendResponse(CAND_FOCAN_PRA, p ? FOCAN_ACK : FOCAN_NACK);

  return p;
}

uint8_t FOCAN_xDownloadFlash(can_rx_t *Rx, uint32_t *size, uint32_t timeout,
                             uint32_t *tick) {
  uint32_t offset, currentSize;
  uint8_t p, percent, len, ptr[BLK_SIZE];
  uint16_t pos = 0;

  // read
  offset = Rx->data.u32[0];
  currentSize = Rx->data.u16[2] + 1;

  // check the flash size
  p = (offset + currentSize) <= APP_MAX_SIZE;
  // Send response
  SendResponse(CAND_FOCAN_INIT, p ? FOCAN_ACK : FOCAN_NACK);

  // Wait data
  len = sizeof(uint32_t);
  if (p) {
    *tick = _GetTickMS();
    do {
      // read
      if (CANBUS_Read(Rx)) {
        if (CANBUS_ReadID(&(Rx->header)) == CAND_FOCAN_RUN) {
          // read
          pos = Rx->data.u16[0];
          memcpy(&ptr[pos], &(Rx->data.u32[1]), len);

          // response ACK
          p = SendResponse(CAND_FOCAN_RUN, pos);
          pos += len;

          // update tick
          *tick = _GetTickMS();
          _LedToggle();
        }
      }
      // handle timeout
      if ((_GetTickMS() - *tick > timeout)) p = 0;

    } while (p && (pos < currentSize));
  }

  // validate received size
  if (p) p = (pos == currentSize);

  // flash to firmware
  if (p) p = FLASHER_WriteAppArea(ptr, currentSize, offset);

  // progress indicator
  if (p) {
    percent = offset * 100 / *size;
    printf("FOTA:Progress = %lu Bytes (%u%%)\n", offset, percent);
  }

  // send final response
  SendResponse(CAND_FOCAN_INIT, p ? FOCAN_ACK : FOCAN_NACK);

  return p;
}

uint8_t FOCAN_xPascaDownload(can_rx_t *Rx, uint32_t *size) {
  uint32_t crc;
  uint8_t p;

  // Read
  crc = Rx->data.u32[0];

  // Execute
  p = FOTA_ValidateCRC(crc, *size, APP_START_ADDR);
  // Glue related information to new image
  if (p) {
    FOTA_SetAppMeta(CRC_OFFSET, &crc);
    FOTA_SetAppMeta(SIZE_OFFSET, size);
  }

  // Send response
  SendResponse(CAND_FOCAN_PASCA, p ? FOCAN_ACK : FOCAN_NACK);

  return p;
}

/* Private functions implementation
 * --------------------------------------------*/
static uint8_t SendSqueeze(uint32_t address, void *data, uint8_t size) {
  uint8_t p, retry = FOCAN_RETRY;
  can_tx_t Tx = {0};

  do {
    // ack
    p = SendResponse(address, FOCAN_ACK);
    // version
    if (p) {
      memcpy(&(Tx.data), data, size);
      p = CANBUS_Write(&Tx, address, size, 0);
    }
    // ack
    if (p) p = SendResponse(address, FOCAN_ACK);

  } while (!p && --retry);

  return p;
}

static uint8_t SendResponse(uint32_t address, uint8_t response) {
  uint8_t p, retry = FOCAN_RETRY;
  can_tx_t Tx = {0};

  do {
    Tx.data.u8[0] = response;
    p = CANBUS_Write(&Tx, address, 1, 0);
  } while (!p && --retry);

  return p;
}
