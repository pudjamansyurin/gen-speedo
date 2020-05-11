/*
 * HMI1.h
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

#ifndef INC_NODES_HMI1_H_
#define INC_NODES_HMI1_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "_defines.h"

/* Exported struct --------------------------------------------------------------*/
typedef struct {
	struct {
		uint8_t abs;
		uint8_t mirror;
		uint8_t lamp;
		uint8_t warning;
		uint8_t overheat;
		uint8_t finger;
		uint8_t keyless;
		uint8_t daylight;
		uint8_t sein_left;
		uint8_t sein_right;
	} status;
	struct {
		sw_mode_t sel;
		uint8_t hide;
		sw_mode_drive_t drive;
		struct {
			sw_mode_trip_t sel;
			uint32_t val;
		} trip;
		struct {
			sw_mode_report_t sel;
			uint8_t val;
		} report;
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

/* Public functions implementation --------------------------------------------*/
void HMI1_Init(void);
uint8_t HMI1_CAN_TX_Heartbeat(void);

#endif /* INC_NODES_HMI1_H_ */
