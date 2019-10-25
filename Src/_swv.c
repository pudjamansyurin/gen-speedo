/*
 * _swv.c
 *
 *  Created on: Sep 23, 2019
 *      Author: Puja
 */

#include "_swv.h"

extern osMutexId SwvMutexHandle;

void SWV_SendChar(char ch) {
#if SWV_DEBUG
	// wait if busy
	while (ITM->PORT[0].u32 == 0)
		;
	// send to ITM0
	ITM->PORT[0].u8 = (uint8_t) ch;
#endif
}

void SWV_SendInt(int32_t num) {
	osMutexWait(SwvMutexHandle, osWaitForever);

	char str[10]; // 10 chars max for INT32_MAX
	int i = 0;
	if (num < 0) {
		SWV_SendChar('-');
		num *= -1;
	}
	do
		str[i++] = num % 10 + '0';
	while ((num /= 10) > 0);
	for (i--; i >= 0; i--)
		SWV_SendChar(str[i]);

	osMutexRelease(SwvMutexHandle);
}

void SWV_SendInt0(int32_t num) {
	osMutexWait(SwvMutexHandle, osWaitForever);

	char str[10]; // 10 chars max for INT32_MAX
	int i = 0;
	if (num < 0) {
		SWV_SendChar('-');
		num *= -1;
	}
	if ((num < 10) && (num >= 0))
		SWV_SendChar('0');
	do
		str[i++] = num % 10 + '0';
	while ((num /= 10) > 0);
	for (i--; i >= 0; i--)
		SWV_SendChar(str[i]);

	osMutexRelease(SwvMutexHandle);
}

void SWV_SendHex8(uint16_t num) {
	osMutexWait(SwvMutexHandle, osWaitForever);

	SWV_SendChar(HEX_CHARS[(num >> 4) % 0x10]);
	SWV_SendChar(HEX_CHARS[(num & 0x0f) % 0x10]);

	osMutexRelease(SwvMutexHandle);
}

void SWV_SendHex16(uint16_t num) {
	osMutexWait(SwvMutexHandle, osWaitForever);

	uint8_t i;
	for (i = 12; i > 0; i -= 4)
		SWV_SendChar(HEX_CHARS[(num >> i) % 0x10]);
	SWV_SendChar(HEX_CHARS[(num & 0x0f) % 0x10]);

	osMutexRelease(SwvMutexHandle);
}

void SWV_SendHex32(uint32_t num) {
	osMutexWait(SwvMutexHandle, osWaitForever);

	uint8_t i;
	for (i = 28; i > 0; i -= 4)
		SWV_SendChar(HEX_CHARS[(num >> i) % 0x10]);
	SWV_SendChar(HEX_CHARS[(num & 0x0f) % 0x10]);

	osMutexRelease(SwvMutexHandle);
}

void SWV_SendStr(char *str) {
	osMutexWait(SwvMutexHandle, osWaitForever);

	while (*str)
		SWV_SendChar(*str++);

	osMutexRelease(SwvMutexHandle);
}

void SWV_SendStrLn(char *str) {
	osMutexWait(SwvMutexHandle, osWaitForever);

	while (*str)
		SWV_SendChar(*str++);
	SWV_SendChar('\n');

	osMutexRelease(SwvMutexHandle);
}

void SWV_SendBuf(char *buf, uint16_t bufsize) {
	osMutexWait(SwvMutexHandle, osWaitForever);

	uint16_t i;
	for (i = 0; i < bufsize; i++)
		SWV_SendChar(*buf++);

	osMutexRelease(SwvMutexHandle);
}

void SWV_SendBufPrintable(char *buf, uint16_t bufsize, char subst) {
	osMutexWait(SwvMutexHandle, osWaitForever);

	uint16_t i;
	char ch;
	for (i = 0; i < bufsize; i++) {
		ch = *buf++;
		SWV_SendChar(ch > 32 ? ch : subst);
	}

	osMutexRelease(SwvMutexHandle);
}

void SWV_SendBufHex(char *buf, uint16_t bufsize) {
	osMutexWait(SwvMutexHandle, osWaitForever);

	uint16_t i;
	char ch;
	for (i = 0; i < bufsize; i++) {
		ch = *buf++;
		SWV_SendChar(HEX_CHARS[(ch >> 4) % 0x10]);
		SWV_SendChar(HEX_CHARS[(ch & 0x0f) % 0x10]);
	}

	osMutexRelease(SwvMutexHandle);
}

void SWV_SendBufHexFancy(char *buf, uint16_t bufsize, uint8_t column_width, char subst) {
	osMutexWait(SwvMutexHandle, osWaitForever);

	uint16_t i = 0, len, pos;
	char buffer[column_width];

	while (i < bufsize) {
		// Line number
		SWV_SendHex16(i);
		SWV_SendChar(':');
		SWV_SendChar(' '); // Faster and less code than SWV_SendStr(": ");

		// Copy one line
		if (i + column_width >= bufsize)
			len = bufsize - i;
		else
			len = column_width;
		memcpy(buffer, &buf[i], len);

		// Hex data
		pos = 0;
		while (pos < len)
			SWV_SendHex8(buffer[pos++]);
		SWV_SendChar(' ');

		// Raw data
		pos = 0;
		do
			SWV_SendChar(buffer[pos] > 32 ? buffer[pos] : subst);
		while (++pos < len);
		SWV_SendChar('\n');

		i += len;
	}

	osMutexRelease(SwvMutexHandle);
}
