/*
 * _config.c
 *
 *  Created on: Aug 26, 2019
 *      Author: Puja
 */

#include "_config.h"

extern RTC_HandleTypeDef hrtc;

void BSP_Led_Write(uint8_t number, uint8_t state) {
	if (number == 1) {
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, state);
	} else {
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, state);
	}
}

void BSP_Led_Toggle(uint8_t number) {
	if (number == 1) {
		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	} else {
		HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
	}
}

void Get_RTC(char *dateTime) {
	RTC_TimeTypeDef currentTime;
	RTC_DateTypeDef currentDate;

	// get the RTC
	HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);

	// combine RTC datetime
	sprintf(dateTime, "20%02d%02d%02d%02d%02d%02d", currentDate.Year, currentDate.Month, currentDate.Date, currentTime.Hours,
			currentTime.Minutes, currentTime.Seconds);
}

void Set_RTC(char *dateTime) {
	// format dateTime: YYYYMMDDHHMMSS
	char Y[2], M[2], D[2], H[2], I[2], S[2];
	RTC_TimeTypeDef currentTime;
	RTC_DateTypeDef currentDate;

	// parsing
	strncpy(Y, dateTime + 2, 2);
	strncpy(M, dateTime + 4, 2);
	strncpy(D, dateTime + 6, 2);
	strncpy(H, dateTime + 8, 2);
	strncpy(I, dateTime + 10, 2);
	strncpy(S, dateTime + 12, 2);

	// assing to object
	currentDate.WeekDay = RTC_WEEKDAY_SUNDAY; // day is ignored
	currentDate.Year = atoi(Y);
	currentDate.Month = atoi(M);
	currentDate.Date = atoi(D);
	currentTime.Hours = atoi(H);
	currentTime.Minutes = atoi(I);
	currentTime.SecondFraction = atoi(S);

	// set the RTC
	HAL_RTC_SetTime(&hrtc, &currentTime, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc, &currentDate, RTC_FORMAT_BIN);
}

