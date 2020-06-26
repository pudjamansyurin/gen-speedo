/*
 * _gui.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Puja
 */

#ifndef GAPP_H_
#define GAPP_H_

/* Includes ------------------------------------------------------------------*/
#include "Libs/_utils.h"

/* GUI Thread prototypes ------------------------------------------------------*/
void StartDisplayTask(void *argument);

/* Struct prototypes -------------------------------------------------------*/
typedef struct {
	GUI_CONST_STORAGE GUI_BITMAP *background;
	struct {
		GUI_POINT points[25];
		int count;
	} overlay;
} display_t;

/* Functions prototypes -------------------------------------------------------*/
void GUI_ClearRectangle(GUI_RECT *rect);
void GUI_IconMem(uint16_t x, uint16_t y, const GUI_BITMAP *fg, uint8_t show, uint8_t alpha);
void GUI_Icon(uint16_t x, uint16_t y, const GUI_BITMAP *fg, uint8_t show, uint8_t alpha);

#endif /* GAPP_H_ */
