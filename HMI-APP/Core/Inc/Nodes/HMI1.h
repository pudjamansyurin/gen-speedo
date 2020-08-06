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
        char mode[SW_M_DRIVE_MAX+1][12];
    } drive;
    struct {
        char mode[SW_M_TRIP_MAX+1][7];
    } trip;
    struct {
        char mode[SW_M_REPORT_MAX+1][6];
        char unit[SW_M_REPORT_MAX+1][11];
    } report;
} sw_mode_t;

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
        uint8_t reverse;
        uint8_t hide;
        SW_MODE sel;

        uint8_t val[SW_M_MAX+1];
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
    sw_mode_t ref;
	hmi1_data_t d;
	hmi1_can_t can;
	void (*Init)(void);
} hmi1_t;

/* Public functions implementation --------------------------------------------*/
void HMI1_Init(void);
uint8_t HMI1_CAN_TX_Heartbeat(void);

#endif /* INC_NODES_HMI1_H_ */
