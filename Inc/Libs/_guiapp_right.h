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
void RIGHT_Sein(latch_t *tmp);
void RIGHT_Warning(latch_t *tmp);
void RIGHT_ABS(latch_t *tmp);
void RIGHT_Temperature(latch_t *tmp);
void RIGHT_Lamp(latch_t *tmp);
void RIGHT_Speed(latch_t *tmp);
void RIGHT_Signal(latch_t *tmp);
void RIGHT_Battery(latch_t *tmp);
void RIGHT_ModeReport(latch_t *tmp);
void RIGHT_ModeDrive(latch_t *tmp);

#endif /* GAPP_RIGHT_H_ */
