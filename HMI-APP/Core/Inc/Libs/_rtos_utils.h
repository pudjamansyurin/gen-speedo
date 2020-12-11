/*
 * _rtos_utils.h
 *
 *  Created on: Dec 11, 2020
 *      Author: pudja
 */

#ifndef INC_LIBS__RTOS_UTILS_H_
#define INC_LIBS__RTOS_UTILS_H_

/* Includes ------------------------------------------------------------------*/
#include "_defines.h"

/* Functions prototypes -------------------------------------------------------*/
uint8_t _RTOS_ThreadFlagsWait(uint32_t *notif, uint32_t flags, uint32_t options, uint32_t timeout);

#endif /* INC_LIBS__RTOS_UTILS_H_ */
