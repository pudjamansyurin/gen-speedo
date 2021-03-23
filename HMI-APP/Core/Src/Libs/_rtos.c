/*
 * _rtos.c
 *
 *  Created on: Mar 22, 2021
 *      Author: pujak
 */

/* Includes ------------------------------------------------------------------*/
#include "Libs/_rtos.h"

/* external variables
 * -----------------------------------------------------------*/
extern osEventFlagsId_t GlobalEventHandle;

/* Public functions implementation
 * --------------------------------------------*/
uint8_t _osFlag(uint32_t *notif, uint32_t flags, uint32_t options, uint32_t timeout) {
  *notif = osThreadFlagsWait(flags, options, timeout);

  if (*notif > FLAG_MASK)
    return 0;

  return (*notif & flags) > 0;
}

uint32_t _osEventManager(void) {
	return osEventFlagsWait(GlobalEventHandle, EVENT_READY, osFlagsNoClear, osWaitForever);
}

uint32_t _osFlagOne(uint32_t *notif, uint32_t flag, uint32_t timeout) {
	return _osFlag(notif, flag, osFlagsWaitAny, timeout);
}

uint32_t _osFlagAny(uint32_t *notif, uint32_t timeout) {
	return _osFlag(notif, FLAG_MASK, osFlagsWaitAny, timeout);
}

