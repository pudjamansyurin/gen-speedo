/*
 * BMS.c
 *
 *  Created on: May 11, 2020
 *      Author: pudja
 */

/* Includes ------------------------------------------------------------------*/
#include "BMS.h"

/* Public variables -----------------------------------------------------------*/
bms_t BMS = {
		.d = { 0 },
		BMS_Init
};

/* Public functions implementation --------------------------------------------*/
void BMS_Init(void) {
	BMS.d.soc = 0;
}
