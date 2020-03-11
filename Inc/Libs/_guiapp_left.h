/*
 * _guiapp_left.h
 *
 *  Created on: Mar 11, 2020
 *      Author: pudja
 */

#ifndef GAPP_LEFT_H_
#define GAPP_LEFT_H_

#include "_utils.h"

void LEFT_Animation(void);
void LEFT_Sein(uint8_t status);
void LEFT_Finger(uint8_t status);
void LEFT_Mirror(uint8_t status);
void LEFT_Keyless(uint8_t status);
void LEFT_Needle(uint8_t deg, uint16_t x, uint16_t y, uint16_t r, uint16_t h, uint8_t max);
void LEFT_Trip(sw_mode_trip_t mode_trip);

#endif /* GAPP_LEFT_H_ */
