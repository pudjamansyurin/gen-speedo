/*
 * _guiapp_left.h
 *
 *  Created on: Mar 11, 2020
 *      Author: pudja
 */

#ifndef GAPP_LEFT_H_
#define GAPP_LEFT_H_

/* Includes ------------------------------------------------------------------*/
#include "Libs/_utils.h"
#if USE_HMI_LEFT

/* Struct prototypes -------------------------------------------------------*/
typedef struct {
	struct {
		GUI_RECT total;
		GUI_RECT sub;
	} trip;
} rect_t;

typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t r;
	uint8_t h;
	uint8_t max;
} collection_t;

/* Functions prototypes -------------------------------------------------------*/
void LEFT_Animation(void);
void LEFT_MemGroupEnter(void);
void LEFT_MemGroupExit(void);
void LEFT_Sein(void);
void LEFT_Finger(void);
void LEFT_Mirror(void);
void LEFT_Keyless(void);
void LEFT_Odometer(void);
void LEFT_ModeTrip(void);
void LEFT_Needle(void);

#endif
#endif /* GAPP_LEFT_H_ */
