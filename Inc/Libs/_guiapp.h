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

typedef struct {
  db_t db;
  struct {
    struct {
      uint8_t trip;
      uint8_t drive;
      uint8_t report;
    } mode;
    struct {
      uint8_t low;
      uint8_t update;
    } soc;
    struct {
      uint8_t low;
      TickType_t tick;
    } battery;
  } flag;
} latch_t;

/* Functions prototypes --------------------------------------------------------*/
void GUI_MainTask(void);

#endif /* GAPP_H_ */
