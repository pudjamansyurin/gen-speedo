/*
 * _guiapp_left.c
 *
 *  Created on: Mar 11, 2020
 *      Author: pudja
 */
/* Includes ------------------------------------------------------------------*/
#include "_guiapp_left.h"

#if USE_HMI_LEFT
#include "HMI_Left_Finger.c"
#include "HMI_Left_Keyless.c"
#include "HMI_Left_Mirror.c"
#include "HMI_Left_Sein.c"
#include "HMI_Left_Trip_A.c"
#include "HMI_Left_Trip_B.c"
#include "HMI_Left.c"
#include "Square721_BT23.c"

/* External variables ------------------------------------------------------------------*/
extern db_t DB;

/* Variables ------------------------------------------------------------------*/
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
rect_t RECT = {
    .trip = {
        .total = { 159, 106, 159 + 64, 106 + 24 },
        .sub = { 159, 83, 159 + 64, 83 + 24 }
    }
};
collection_t COL = {
    .x = 58,
    .y = 161,
    .r = 123,
    .h = 7,
    .max = 112
};

/* Functions -----------------------------------------------------------------*/
void LEFT_Animation(void) {
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

void LEFT_Sein(latch_t *tmp) {
  if (tmp->db.hmi1.status.sein_left != DB.hmi1.status.sein_left) {
    tmp->db.hmi1.status.sein_left = DB.hmi1.status.sein_left;

    _GUI_Indicator(GAPP.background, &bmHMI_Left_Sein, 275, 84, DB.hmi1.status.sein_left, 200);
  }
}

void LEFT_Finger(latch_t *tmp) {
  if (tmp->reset || tmp->db.hmi1.status.finger != DB.hmi1.status.finger) {
    tmp->db.hmi1.status.finger = DB.hmi1.status.finger;

    _GUI_Indicator(GAPP.background, &bmHMI_Left_Finger, 293, 127, DB.hmi1.status.finger, 200);
  }
}

void LEFT_Mirror(latch_t *tmp) {
  if (tmp->reset || tmp->db.hmi1.status.mirror != DB.hmi1.status.mirror) {
    tmp->db.hmi1.status.mirror = DB.hmi1.status.mirror;

    _GUI_Indicator(GAPP.background, &bmHMI_Left_Mirror, 261, 129, DB.hmi1.status.mirror, 200);
  }
}

uint8_t LEFT_NeedUpdate(latch_t *tmp) {
  return (tmp->reset
      || tmp->db.hmi1.mode.trip.sel != DB.hmi1.mode.trip.sel
      || tmp->db.hmi1.mode.trip.val != DB.hmi1.mode.trip.val
      || tmp->db.vcu.odometer != DB.vcu.odometer
      || tmp->db.mcu.rpm != DB.mcu.rpm
      || tmp->db.hmi1.status.keyless != DB.hmi1.status.keyless
      || tmp->flag.mode.trip != (DB.hmi1.mode.sel == SW_M_TRIP && DB.hmi1.mode.hide)
  );
}

void LEFT_Keyless(latch_t *tmp) {
  tmp->db.hmi1.status.keyless = DB.hmi1.status.keyless;

  _GUI_Indicator(GAPP.background, &bmHMI_Left_Keyless, 228, 133, DB.hmi1.status.keyless, 200);
}

void LEFT_Odometer(latch_t *tmp) {
  char str[20];

  tmp->db.vcu.odometer = DB.vcu.odometer;
  GUI_SetFont(&GUI_FontSquare721_BT23);
  sprintf(str, "%05u", (unsigned int) DB.vcu.odometer);
  GUI_DispStringInRectWrap(str, &(RECT.trip.total), GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
}

void LEFT_ModeTrip(latch_t *tmp) {
  char str[20];
  const uint16_t x = 129, y = 89;
  GUI_CONST_STORAGE GUI_BITMAP *pImage;

  tmp->db.hmi1.mode.trip.sel = DB.hmi1.mode.trip.sel;
  tmp->flag.mode.trip = (DB.hmi1.mode.sel == SW_M_TRIP && DB.hmi1.mode.hide);

  // Mode Trip Label
  if (!tmp->flag.mode.trip) {
    // Decide the image
    if (DB.hmi1.mode.trip.sel == SW_M_TRIP_A) {
      pImage = &bmHMI_Left_Trip_A;
    } else {
      pImage = &bmHMI_Left_Trip_B;
    }
    _GUI_Indicator(GAPP.background, pImage, x, y, 1, 254);
  }

  // Mode Trip Value
  tmp->db.hmi1.mode.trip.val = DB.hmi1.mode.trip.val;
  GUI_SetFont(&GUI_FontSquare721_BT23);
  sprintf(str, "%05u", (unsigned int) DB.hmi1.mode.trip.val);
  GUI_DispStringInRectWrap(str, &(RECT.trip.sub), GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
}

void LEFT_Needle(latch_t *tmp, collection_t *col) {
  uint8_t deg = DB.mcu.rpm <= MCU_RPM_MAX ? DB.mcu.rpm * col->max / MCU_RPM_MAX : col->max;
  GUI_POINT pNeedle[] = {
      {
          (col->x + col->r) + (((col->h / 2) + 1) * cos(_D2R(deg + 270))),
          (col->y + (col->h / 2) + 1) + (((col->h / 2) + 1) * sin(_D2R(deg + 270)))
      }, // top
      {
          (col->x + col->r) + (col->r * cos(_D2R(deg + 180))),
          (col->y + (col->h / 2) + 1) + (col->r * sin(_D2R(deg + 180)))
      }, // corner
      {
          (col->x + col->r) + (((col->h / 2) + 1) * cos(_D2R(deg + 90))),
          (col->y + (col->h / 2) + 1) + (((col->h / 2) + 1) * sin(_D2R(deg + 90)))
      } // bottom
  };

  tmp->db.mcu.rpm = DB.mcu.rpm;

  GUI_SetColor(GUI_RED);
  GUI_AA_SetFactor(6);
  GUI_SetAlpha(205);
  GUI_AA_FillPolygon(pNeedle, GUI_COUNTOF(pNeedle), 0, 0);
  GUI_SetAlpha(255);
  GUI_AA_FillCircle(col->x + col->r, col->y + (col->h / 2) + 1, (col->h / 2) + 2);
  GUI_AA_SetFactor(1);
}

#endif
