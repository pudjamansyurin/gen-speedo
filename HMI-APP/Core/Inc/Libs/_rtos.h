/*
 * _rtos.h
 *
 *  Created on: Mar 22, 2021
 *      Author: pujak
 */

#ifndef INC_LIBS__RTOS_H_
#define INC_LIBS__RTOS_H_

/* Includes
 * --------------------------------------------*/
#include "_defs.h"

/* Exported constants
 * --------------------------------------------*/
#define EVENT_READY BIT(0)
#define EVENT_MASK ((uint32_t)0xFFFFFF)
#define FLAG_MASK ((uint32_t)0x7FFFFFFF)

/* Public functions prototype
 * --------------------------------------------*/
uint32_t _osEventManager(void);
uint8_t _osFlag(uint32_t *notif, uint32_t flags, uint32_t options,
                uint32_t timeout);
uint32_t _osFlagOne(uint32_t *notif, uint32_t flag, uint32_t timeout);
uint32_t _osFlagAny(uint32_t *notif, uint32_t timeout);

#endif /* INC_LIBS__RTOS_H_ */
