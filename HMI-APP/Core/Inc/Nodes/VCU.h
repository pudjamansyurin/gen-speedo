/*
 * VCU.h
 *
 *  Created on: May 11, 2020
 *      Author: Pudja Mansyurin
 */

#ifndef INC_NODES_VCU_H_
#define INC_NODES_VCU_H_

/* Includes
 * --------------------------------------------*/
#include "App/_common.h"
#include "Drivers/_canbus.h"

/* Exported constants
 * --------------------------------------------*/
#define VCU_TIMEOUT_MS ((uint32_t)5000)

/* Exported structs
 * --------------------------------------------*/
typedef struct {
  uint8_t run;
  uint8_t soc;
} bms_data_t;

typedef struct {
  uint8_t run;
  uint8_t discur;
  uint8_t speed;
} mcu_data_t;

typedef struct {
  uint8_t connected;
  uint32_t tick;
  uint8_t signal;
  int8_t state;
  bms_data_t bms;
  mcu_data_t mcu;
} vcu_data_t;

typedef struct {
  vcu_data_t d;
} vcu_t;

/* Exported variables
 * --------------------------------------------*/
extern vcu_t VCU;

/* Public functions prototype
 * --------------------------------------------*/
void VCU_Init(void);
void VCU_RX_SwitchControl(can_rx_t *Rx);
void VCU_RX_ModeData(can_rx_t *Rx);

#endif /* INC_NODES_VCU_H_ */
