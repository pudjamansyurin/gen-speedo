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
	uint8_t mode[HBAR_M_MAX];
	uint8_t report;
	uint16_t trip;
} hbar_data_t;

typedef struct {
  HBAR_MODE m;
  hbar_data_t d;
	uint8_t reverse;
	uint8_t hide;
} hbar_t;

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
		uint8_t registering;
	} state;
	struct {
		uint8_t left;
		uint8_t right;
	} sein;
} hmi1_data_t;

typedef struct {
	hbar_t hbar;
	hmi1_data_t d;
	struct {
		uint8_t (*Heartbeat)(void);
	} t;
	void (*Init)(void);
	void (*Flush)(void);
} hmi1_t;

/* Exported variables ---------------------------------------------------------*/
extern hmi1_t HMI1;

/* Public functions implementation --------------------------------------------*/
void HMI1_Init(void);
void HMI1_Flush(void);
uint8_t HMI1_TX_Heartbeat(void);

#endif /* INC_NODES_HMI1_H_ */
