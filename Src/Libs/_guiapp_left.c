/*
 * _guiapp_left.c
 *
 *  Created on: Mar 11, 2020
 *      Author: pudja
 */

#include "_guiapp_left.h"

#if USE_HMI_LEFT
#include "HMI_Left_Finger.c"
#include "HMI_Left_Keyless.c"
#include "HMI_Left_Mirror.c"
#include "HMI_Left_Sein.c"
#include "HMI_Left_Trip_A.c"
#include "HMI_Left_Trip_B.c"
#include "HMI_Left.c"

guiapp_t GAPP = {
    .background = &bmHMI_Left,
    .overlay = {
        .points = {
            { 300, 66 },
            { 257, 66 },
            { 230, 39 },
            { 144, 39 },
            { 87, 66 },
            { 39, 175 },
            { 55, 205 },
            { 215, 205 },
            { 250, 153 },
            { 300, 153 }
        },
        .count = 10
    }
};

void LEFT_Animation(void){
  uint16_t k;

  for (k = 0; k <= 20; k++) {
    GUI_FillRect(40, 120 - 1, 40 + k, 170);
    GUI_Delay(20);
  }
  for (k = 0; k <= 180; k++) {
    GUI_DrawPie(60, 120 - 1, 250, 270, 270 + k, 0);
    GUI_Delay(10);
  }
  for (k = 0; k <= 20; k++) {
    GUI_FillRect(60 - k, 50, 60, 120 - 1);
    GUI_Delay(20);
  }
}

void LEFT_Sein(uint8_t status) {
  _Indicator(GAPP.background, &bmHMI_Left_Sein, 275, 84, status, 200);
}

void LEFT_Finger(uint8_t status) {
  _Indicator(GAPP.background, &bmHMI_Left_Finger, 293, 127, status, 200);
}

void LEFT_Mirror(uint8_t status) {
  _Indicator(GAPP.background, &bmHMI_Left_Mirror, 261, 129, status, 200);
}

void LEFT_Keyless(uint8_t status) {
  _Indicator(GAPP.background, &bmHMI_Left_Keyless, 228, 133, status, 200);
}

void LEFT_Trip(sw_mode_trip_t mode_trip) {
  const uint16_t x = 129, y = 89;
  GUI_CONST_STORAGE GUI_BITMAP *pImage;

  // decide the image
  if (mode_trip == SW_M_TRIP_A) {
    pImage = &bmHMI_Left_Trip_A;
  } else {
    pImage = &bmHMI_Left_Trip_B;
  }

  _Indicator(GAPP.background, pImage, x, y, 1, 254);
}

void LEFT_Needle(uint8_t deg, uint16_t x, uint16_t y, uint16_t r, uint16_t h, uint8_t max) {
  GUI_POINT aPoints_Needle[] = {
      {
          (x + r) + (((h / 2) + 1) * cos(_D2R(deg + 270))),
          (y + (h / 2) + 1) + (((h / 2) + 1) * sin(_D2R(deg + 270)))
      }, //atas
      {
          (x + r) + (r * cos(_D2R(deg + 180))),
          (y + (h / 2) + 1) + (r * sin(_D2R(deg + 180)))
      }, //ujung
      {
          (x + r) + (((h / 2) + 1) * cos(_D2R(deg + 90))),
          (y + (h / 2) + 1) + (((h / 2) + 1) * sin(_D2R(deg + 90)))
      } //bawah
  };

  GUI_SetColor(GUI_RED);
  GUI_AA_SetFactor(6);
  GUI_SetAlpha(205);
  GUI_AA_FillPolygon(aPoints_Needle, GUI_COUNTOF(aPoints_Needle), 0, 0);
  GUI_SetAlpha(255);
  GUI_AA_FillCircle(x + r, y + (h / 2) + 1, (h / 2) + 2);
  GUI_AA_SetFactor(1);
}

#endif
