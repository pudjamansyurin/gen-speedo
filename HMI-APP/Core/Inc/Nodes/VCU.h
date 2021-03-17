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

/* Exported constants --------------------------------------------------------*/
#define VCU_TIMEOUT    					 (uint32_t) 5000					// ms
#define MCU_SPEED_MAX 			      (uint8_t) 150
#define MCU_RPM_MAX 			       (uint32_t) 99999

/* Exported struct -----------------------------------------------------------*/
typedef struct {
	uint8_t soc;
} bms_data_t;

typedef struct {
	uint32_t rpm;
  uint8_t speed;
	uint32_t temperature;
} mcu_data_t;

typedef struct {
  uint8_t signal;
  uint32_t tick;
	bms_data_t bms;
	mcu_data_t mcu;
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
