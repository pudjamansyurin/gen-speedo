/*
 * _utils.h
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/* Includes ------------------------------------------------------------------*/
#include "_database.h"
#include "_log.h"

/* Functions prototypes -------------------------------------------------------*/
void _GUI_ClearRect(GUI_RECT *rect);
void _GUI_IconMem(uint16_t x, uint16_t y, const GUI_BITMAP *fg, uint8_t show, uint8_t alpha);
void _GUI_Icon(uint16_t x, uint16_t y, const GUI_BITMAP *fg, uint8_t show, uint8_t alpha);

void _LedWrite(uint8_t number, uint8_t state);
void _LedToggle(uint8_t number);

uint8_t _RTOS_ValidThreadFlag(uint32_t flag);
uint8_t _RTOS_ValidEventFlag(uint32_t flag);

void _SetBacklight(uint8_t state);
float _D2R(uint16_t deg);

#endif /* CONFIG_H_ */
