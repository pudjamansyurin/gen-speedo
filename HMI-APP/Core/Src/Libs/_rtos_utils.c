/*
 * _rtos_utils.c
 *
 *  Created on: Dec 11, 2020
 *      Author: pudja
 */

/* Includes ------------------------------------------------------------------*/
#include "Libs/_rtos_utils.h"

/* Private functions declarations --------------------------------------------*/
static uint8_t _RTOS_ValidThreadFlag(uint32_t flag);
//static uint8_t _RTOS_ValidEventFlag(uint32_t flag);

/* Public functions implementations ------------------------------------------*/
uint8_t _RTOS_ThreadFlagsWait(uint32_t *notif, uint32_t flags, uint32_t options, uint32_t timeout) {
  *notif = osThreadFlagsWait(flags, options, timeout);

  return _RTOS_ValidThreadFlag(*notif);
}

/* Private functions implementation --------------------------------------------*/
static uint8_t _RTOS_ValidThreadFlag(uint32_t flag) {
  uint8_t ret = 1;

  // check is empty
  if (!flag)
    ret = 0;
  else if (flag & (~EVT_MASK ))
    ret = 0;

  return ret;
}

//static uint8_t _RTOS_ValidEventFlag(uint32_t flag) {
//  uint8_t ret = 1;
//
//  // check is empty
//  if (!flag)
//    ret = 0;
//  else if (flag & (~EVENT_MASK ))
//    ret = 0;
//
//  return ret;
//}
