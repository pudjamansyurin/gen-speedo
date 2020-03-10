/*
 * _utils.h
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdlib.h>				// for: itoa()
#include <stdio.h>				// for: sprintf()
#include <math.h>					// for: M_PI
#include <string.h>             // for: strlen()
#include <limits.h>
#include "_database.h"
#include "_log.h"

// Function prototype
void BSP_Led_Write(uint8_t number, uint8_t state);
void BSP_Led_Toggle(uint8_t number);
void BSP_Set_Backlight(uint8_t state);
float D2R(uint16_t deg);

#endif /* CONFIG_H_ */
