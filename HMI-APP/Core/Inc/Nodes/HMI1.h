/*
 * HMI1.h
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

#ifndef INC_NODES_HMI1_H_
#define INC_NODES_HMI1_H_

/* Includes ------------------------------------------------------------------*/
#include "Libs/_utils.h"

/* Exported struct -----------------------------------------------------------*/
typedef struct {
  struct {
    uint8_t abs;
    uint8_t mirroring;
    uint8_t lamp;
    uint8_t warning;
    uint8_t overheat;
    uint8_t unfinger;
    uint8_t unremote;
    uint8_t daylight;
  } state;
  struct {
    uint8_t left;
    uint8_t right;
  } sein;
  struct {
    uint8_t reverse;
    uint8_t hide;
    uint8_t sel;

    uint8_t val[HBAR_M_MAX];
    uint8_t report;
    uint32_t trip;
  } mode;
} hmi1_data_t;

typedef struct {
  struct {
    uint8_t (*Heartbeat)(void);
  } t;
} hmi1_can_t;

typedef struct {
  hmi1_data_t d;
  hmi1_can_t can;
  void (*Init)(void);
} hmi1_t;

/* Exported variables ---------------------------------------------------------*/
extern hmi1_t HMI1;

/* Public functions implementation --------------------------------------------*/
void HMI1_Init(void);
uint8_t HMI1_CAN_TX_Heartbeat(void);

#endif /* INC_NODES_HMI1_H_ */
