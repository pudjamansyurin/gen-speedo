/*
 * _gui.h
 *
 *  Created on: Oct 21, 2019
 *      Author: Puja
 */

#ifndef GAPP_H_
#define GAPP_H_

/* Includes ------------------------------------------------------------------*/
#include "_can.h"
#if USE_HMI_LEFT
#include "_guiapp_left.h"
#else
#include "_guiapp_right.h"
#endif

/* Functions prototypes --------------------------------------------------------*/
void GUI_MainTask(void);

#endif /* GAPP_H_ */
