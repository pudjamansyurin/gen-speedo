/*
 * _guiapp_right.h
 *
 *  Created on: Mar 11, 2020
 *      Author: pudja
 */

#ifndef GAPP_RIGHT_H_
#define GAPP_RIGHT_H_

#include "_utils.h"

void RIGHT_Animation(void);
void RIGHT_Sein(uint8_t status);
void RIGHT_Warning(uint8_t status);
void RIGHT_ABS(uint8_t status);
void RIGHT_Temperature(uint8_t status);
void RIGHT_Lamp(uint8_t status);
void RIGHT_Battery(int8_t status);

#endif /* GAPP_RIGHT_H_ */
