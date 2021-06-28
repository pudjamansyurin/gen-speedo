/*
 * _can.h
 *
 *  Created on: Oct 7, 2019
 *      Author: Puja
 */

#ifndef CANBUS_H_
#define CANBUS_H_

/* Includes
 * --------------------------------------------*/
#include "App/_common.h"

/* Exported constants
 * --------------------------------------------*/
#define CAN_DATA UNION64
#define CAN_RX_MS ((uint16_t)1000)

/* Exported enums
 * --------------------------------------------*/
typedef enum {
  CAND_FOCAN_PROGRESS = 0x01A,
  CAND_FOCAN_CRC = 0x01B,
  CAND_FOCAN_PRA = 0x01C,
  CAND_FOCAN_INIT = 0x01D,
  CAND_FOCAN_RUN = 0x01E,
  CAND_FOCAN_PASCA = 0x01F,

  CAND_VCU_SWITCH_CTL = 0x02A,
  CAND_VCU_MODE_DATA = 0x02B,
  CAND_VCU_DATETIME = 0x02C,

  CAND_VCU = 0x7A0,
  CAND_HMI1 = 0x7A1,
  CAND_HMI2 = 0x7A2,

} CAN_ADDR;

/* Exported structs
 * --------------------------------------------*/
typedef struct {
  CAN_TxHeaderTypeDef header;
  CAN_DATA data;
} can_tx_t;

typedef struct {
  CAN_RxHeaderTypeDef header;
  CAN_DATA data;
} can_rx_t;

typedef struct {
  CAN_HandleTypeDef *pcan;
} can_t;

/* Public functions prototype
 * --------------------------------------------*/
void CANBUS_Init(void);
void CANBUS_DeInit(void);
uint8_t CANBUS_Filter(void);
uint8_t CANBUS_Write(can_tx_t *Tx, uint32_t address, uint32_t DLC, uint8_t ext);
uint8_t CANBUS_Read(can_rx_t *Rx);
uint32_t CANBUS_ReadID(CAN_RxHeaderTypeDef *RxHeader);

#endif /* CANBUS_H_ */
