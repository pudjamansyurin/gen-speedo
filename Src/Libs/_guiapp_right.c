/*
 * _guiapp_right.c
 *
 *  Created on: Mar 11, 2020
 *      Author: pudja
 */

#include "_guiapp_right.h"

#if !USE_HMI_LEFT
#include "HMI_Right_Abs.c"
#include "HMI_Right_Warning.c"
#include "HMI_Right_Temp.c"
#include "HMI_Right_Lamp.c"
#include "HMI_Right_Sein.c"
#include "HMI_Right_Battery_Full.c"
#include "HMI_Right_Battery_Low.c"
#include "HMI_Right.c"

guiapp_t GAPP = {
    .background = &bmHMI_Right,
    .overlay = {
        .points = {
            { LCD_SIZE_X - 300, 66 },
            { LCD_SIZE_X - 257, 66 },
            { LCD_SIZE_X - 230, 39 },
            { LCD_SIZE_X - 144, 39 },
            { LCD_SIZE_X - 87, 66 },
            { LCD_SIZE_X - 87, 66 },
            { 273, 135 },
            { 275, 140 },
            { LCD_SIZE_X - 39, 175 },
            { LCD_SIZE_X - 55, 205 },
            { 150, 205 },
            { 175, 180 },
            { 170, 145 },
            { 150, 128 },
            { 120, 128 },
            { 100, 150 },
            { 100, 180 },
            { 120, 205 },
            { LCD_SIZE_X - 215, 205 },
            { LCD_SIZE_X - 250, 153 },
            { LCD_SIZE_X - 300, 153 }
        },
        .count = 21
    }
};

void RIGHT_Animation(void){
  uint16_t k;

  for (k = 0; k <= 20; k++) {
    GUI_FillRect(320 - 40 - k, 120 - 1, 320 - 40, 170);
    GUI_Delay(20);
  }
  for (k = 0; k <= 180; k++) {
    GUI_DrawPie(320 - 60, 120 - 1, 250, 270 - k, 270, 0);
    GUI_Delay(10);
  }
  for (k = 0; k <= 20; k++) {
    GUI_FillRect(320 - 60, 50, 320 - 60 + k, 120 - 1);
    GUI_Delay(20);
  }
}

void RIGHT_Sein(uint8_t status) {
  _Indicator(GAPP.background, &bmHMI_Right_Sein, 20, 83, status, 200);
}

void RIGHT_Temperature(uint8_t status) {
  _Indicator(GAPP.background, &bmHMI_Right_Temp, 34, 131, status, 200);
}

void RIGHT_Lamp(uint8_t status) {
  _Indicator(GAPP.background, &bmHMI_Right_Lamp, 190, 136, status, 200);
}

void RIGHT_Warning(uint8_t status) {
  _Indicator(GAPP.background, &bmHMI_Right_Warning, 4, 130, status, 200);
}

void RIGHT_ABS(uint8_t status) {
  _Indicator(GAPP.background, &bmHMI_Right_Abs, 63, 135, status, 200);
}

void RIGHT_Battery(int8_t status) {
  GUI_CONST_STORAGE GUI_BITMAP *bmHMI_Right_Battery = (status > 20 ? &bmHMI_Right_Battery_Full : &bmHMI_Right_Battery_Low);
  _Indicator(GAPP.background, bmHMI_Right_Battery, 195, 170, (status != -1), 200);
}

#endif
