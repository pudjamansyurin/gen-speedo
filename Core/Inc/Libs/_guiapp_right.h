/*
 * _guiapp_right.h
 *
 *  Created on: Mar 11, 2020
 *      Author: pudja
 */

#ifndef GAPP_RIGHT_H_
#define GAPP_RIGHT_H_

/* Includes ------------------------------------------------------------------*/
#include "_utils.h"

/* Struct prototypes -------------------------------------------------------*/
typedef struct {
	GUI_RECT speed;
	GUI_RECT signal;
	GUI_RECT drive;
	struct {
		GUI_RECT value;
		GUI_RECT unit;
	} battery;
	struct {
		GUI_RECT mode;
		GUI_RECT value;
		GUI_RECT unit;
	} report;
} rect_t;

typedef struct {
	struct {
		char mode[2][8];
		char unit[2][7];
	} report;
	struct {
		char mode[4];
	} drive;
} collection_t;

/* Functions prototypes -------------------------------------------------------*/
void RIGHT_Animation(void);
void RIGHT_Sein(void);
void RIGHT_Warning(void);
void RIGHT_ABS(void);
void RIGHT_Overheat(void);
void RIGHT_Lamp(void);
void RIGHT_Speed(void);
void RIGHT_Signal(void);
void RIGHT_Battery(void);
void RIGHT_ModeReport(void);
void RIGHT_ModeDrive(void);

#endif /* GAPP_RIGHT_H_ */
