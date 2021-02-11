/*
 * VCU.h
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

#ifndef INC_NODES_VCU_H_
#define INC_NODES_VCU_H_

/* Includes ------------------------------------------------------------------*/
#include "Libs/_utils.h"
#include "Drivers/_canbus.h"

/* Exported struct -----------------------------------------------------------*/
typedef struct {
  uint8_t signal;
  uint8_t speed;
  struct {
    uint32_t canRx;
  } tick;
} vcu_data_t;

typedef struct {
  struct {
    void (*SwitchModeControl)(can_rx_t*);
    void (*MixedData)(can_rx_t*);
    void (*TripData)(can_rx_t*);
  } r;
} vcu_can_t;

typedef struct {
  vcu_data_t d;
  vcu_can_t can;
  void (*Init)(void);
} vcu_t;

/* Exported variables ---------------------------------------------------------*/
extern vcu_t VCU;

/* Public functions implementation --------------------------------------------*/
void VCU_Init(void);
void VCU_CAN_RX_SwitchModeControl(can_rx_t *Rx);
void VCU_CAN_RX_MixedData(can_rx_t *Rx);
void VCU_CAN_RX_TripData(can_rx_t *Rx);

#endif /* INC_NODES_VCU_H_ */
