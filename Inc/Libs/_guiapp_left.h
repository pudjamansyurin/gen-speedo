/*
 * _guiapp_left.h
 *
 *  Created on: Mar 11, 2020
 *      Author: pudja
 */

#ifndef GAPP_LEFT_H_
#define GAPP_LEFT_H_

/* Includes ------------------------------------------------------------------*/
#include "_utils.h"

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
void LEFT_Sein(latch_t *tmp);
void LEFT_Finger(latch_t *tmp);
void LEFT_Mirror(latch_t *tmp);
void LEFT_Keyless(latch_t *tmp);
void LEFT_Odometer(latch_t *tmp);
void LEFT_ModeTrip(latch_t *tmp);
void LEFT_Needle(latch_t *tmp, collection_t *col);

#endif /* GAPP_LEFT_H_ */
