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
void _GUI_ClearRect(GUI_RECT *rect);
void _GUI_Indicator(const GUI_BITMAP *bg, const GUI_BITMAP *fg, uint16_t x, uint16_t y, uint8_t status, uint8_t alpha);
void _LedWrite(uint8_t number, uint8_t state);
void _LedToggle(uint8_t number);
void _SetBacklight(uint8_t state);
float _D2R(uint16_t deg);

#endif /* CONFIG_H_ */
