/*
 * _swv.h
 *
 *  Created on: Sep 23, 2019
 *      Author: Puja
 */

#ifndef SWV_H_
#define SWV_H_

#include "main.h"
#include "string.h"
#include "cmsis_os.h"

#define SWV_DEBUG 			0
#define HEX_CHARS      "0123456789ABCDEF"

void SWV_SendChar(char ch);

void SWV_SendInt(int32_t num);
void SWV_SendInt0(int32_t num);
void SWV_SendHex8(uint16_t num);
void SWV_SendHex16(uint16_t num);
void SWV_SendHex32(uint32_t num);

void SWV_SendStr(char *str);
void SWV_SendStrLn(char *str);

void SWV_SendBuf(char *buf, uint16_t bufsize);
void SWV_SendBufPrintable(char *buf, uint16_t bufsize, char subst);
void SWV_SendBufHex(char *buf, uint16_t bufsize);
void SWV_SendBufHexFancy(char *buf, uint16_t bufsize, uint8_t column_width, char subst);

#endif /* SWV_H_ */
