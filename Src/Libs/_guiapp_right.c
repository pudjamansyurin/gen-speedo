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
#include "Square721_BT10.c"
#include "Square721_BT14.c"
#include "Square721_BT17.c"
#include "Square721_BT31.c"
#include "Square721_BT60.c"
#include "Square721_Cn_BT62.c"

extern db_t DB;

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
rect_t RECT = {
    .speed = { 83, 79, 85 + 102, 79 + 50 },
    .signal = { 122, 50, 122 + 65, 50 + 10 },
    .drive = { 126, 145, 126 + 26, 145 + 40 },
    .battery = {
        .value = { 227, 164, 227 + 35, 164 + 28 },
        .unit = { 266, 170, 266 + 17, 170 + 17 }
    },
    .report = {
        .mode = { 174 + (-10), 191, 174 + 50 + (-10), 191 + 13 },
        .value = { 228 + (-10), 190, 228 + 20 + (-10), 190 + 15 },
        .unit = { 251 + (-10), 194, 251 + 28 + (-10), 194 + 10 }
    }
};

collection_t COL = {
    .drive = {
        .mode = { 'E', 'S', 'P', 'R' }
    },
    .report = {
        .mode = { "Range", "Average" },
        .unit = { "KM", "KM/KWh" },
    }
};

void RIGHT_Animation(void) {
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

void RIGHT_Sein(latch_t *tmp) {
  if (tmp->db.hmi1.status.sein_right != DB.hmi1.status.sein_right) {
    tmp->db.hmi1.status.sein_right = DB.hmi1.status.sein_right;

    _GUI_Indicator(GAPP.background, &bmHMI_Right_Sein, 20, 83, DB.hmi1.status.sein_right, 200);
  }
}

void RIGHT_Warning(latch_t *tmp) {
  if (tmp->init || tmp->db.hmi1.status.warning != DB.hmi1.status.warning) {
    tmp->db.hmi1.status.warning = DB.hmi1.status.warning;

    _GUI_Indicator(GAPP.background, &bmHMI_Right_Warning, 4, 130, DB.hmi1.status.warning, 200);
  }
}

void RIGHT_ABS(latch_t *tmp) {
  if (tmp->init || tmp->db.hmi1.status.abs != DB.hmi1.status.abs) {
    tmp->db.hmi1.status.abs = DB.hmi1.status.abs;

    _GUI_Indicator(GAPP.background, &bmHMI_Right_Abs, 63, 135, DB.hmi1.status.abs, 200);
  }
}

void RIGHT_Temperature(latch_t *tmp) {
  if (tmp->init || tmp->db.hmi1.status.temperature != DB.hmi1.status.temperature) {
    tmp->db.hmi1.status.temperature = DB.hmi1.status.temperature;

    _GUI_Indicator(GAPP.background, &bmHMI_Right_Temp, 34, 131, DB.hmi1.status.temperature, 200);
  }
}

void RIGHT_Lamp(latch_t *tmp) {
  if (tmp->init || tmp->db.hmi1.status.lamp != DB.hmi1.status.lamp) {
    tmp->db.hmi1.status.lamp = DB.hmi1.status.lamp;

    _GUI_Indicator(GAPP.background, &bmHMI_Right_Lamp, 190, 136, DB.hmi1.status.lamp, 200);
  }
}

void RIGHT_Speed(latch_t *tmp) {
  char str[20];

  if (tmp->init || tmp->db.vcu.speed != DB.vcu.speed) {
    tmp->db.vcu.speed = DB.vcu.speed;

    GUI_SetFont(&GUI_FontSquare721_BT60);
    sprintf(str, "%03u", DB.vcu.speed);
    GUI_DispStringInRectWrap(str, &(RECT.speed), GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
  }
}

void RIGHT_Signal(latch_t *tmp) {
  if (tmp->init || tmp->db.vcu.signal != DB.vcu.signal) {
    tmp->db.vcu.signal = DB.vcu.signal;

    // fill all black
    GUI_SetBkColor(GUI_BLACK);
    _GUI_ClearRect(&(RECT.signal));
    // clear some transparent
    GUI_SetBkColor(GUI_TRANSPARENT);
    GUI_ClearRect(
        RECT.signal.x0,
        RECT.signal.y0,
        RECT.signal.x0 + (DB.vcu.signal * (RECT.signal.x1 - RECT.signal.x0) / 100),
        RECT.signal.y1
        );
    // reset the bg color
    GUI_SetBkColor(GUI_BLACK);
  }
}

void RIGHT_Battery(latch_t *tmp) {
  char str[20];
  int8_t status;
  GUI_CONST_STORAGE GUI_BITMAP *bmHMI_Right_Battery;

  // Detect trigger event
  if (DB.bms.soc <= 20) {
    if (!tmp->flag.soc.low) {
      tmp->flag.soc.low = 1;
      tmp->flag.battery.low = 0;
      tmp->flag.soc.update = 1;
    } else if ((osKernelSysTick() - tmp->flag.battery.tick) >= pdMS_TO_TICKS(500)) {
      tmp->flag.battery.tick = osKernelSysTick();
      tmp->flag.battery.low = !tmp->flag.battery.low;
      tmp->flag.soc.update = 1;
    }
  } else if (DB.bms.soc > 20 && tmp->flag.soc.low) {
    tmp->flag.soc.low = 0;
    tmp->flag.battery.low = 0;
    tmp->flag.soc.update = 1;
  }

  // Battery Icon & Unit
  if (tmp->init || tmp->flag.soc.update) {
    tmp->flag.soc.update = 0;

    // Battery Icon
    status = tmp->flag.battery.low ? -1 : DB.bms.soc;
    bmHMI_Right_Battery = (status > 20 ? &bmHMI_Right_Battery_Full : &bmHMI_Right_Battery_Low);
    _GUI_Indicator(GAPP.background, bmHMI_Right_Battery, 195, 170, (status != -1), 200);

    // Battery Unit
    if (DB.bms.soc <= 20) {
      GUI_SetColor(0xFFE62129);
    }
    _GUI_ClearRect(&(RECT.battery.unit));
    GUI_SetFont(&GUI_FontSquare721_BT17);
    sprintf(str, "%c", '%');
    GUI_DispStringInRectWrap(str, &(RECT.battery.unit), GUI_TA_BOTTOM | GUI_TA_LEFT, GUI_WRAPMODE_NONE);
    GUI_SetColor(0xFFC0C0C0);
  }

  // Battery Value
  if (tmp->init || tmp->db.bms.soc != DB.bms.soc) {
    tmp->db.bms.soc = DB.bms.soc;

    GUI_SetFont(&GUI_FontSquare721_BT31);
    sprintf(str, "%02u", DB.bms.soc);
    GUI_DispStringInRectWrap(str, &(RECT.battery.value), GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
  }
}

void RIGHT_ModeReport(latch_t *tmp) {
  char str[20];

  // Mode Report Unit
  if (tmp->init || tmp->db.hmi1.mode.report.sel != DB.hmi1.mode.report.sel) {
    _GUI_ClearRect(&(RECT.report.unit));
    GUI_SetFont(&GUI_FontSquare721_BT10);
    sprintf(str, "%s", COL.report.unit[DB.hmi1.mode.report.sel]);
    GUI_DispStringInRectWrap(str, &(RECT.report.unit), GUI_TA_BOTTOM | GUI_TA_LEFT, GUI_WRAPMODE_NONE);
  }

  // Mode Report Label
  if (tmp->init
      || tmp->db.hmi1.mode.report.sel != DB.hmi1.mode.report.sel
      || tmp->flag.mode.report != (DB.hmi1.mode.sel == SW_M_REPORT && DB.hmi1.mode.hide)) {
    tmp->db.hmi1.mode.report.sel = DB.hmi1.mode.report.sel;
    tmp->flag.mode.report = (DB.hmi1.mode.sel == SW_M_REPORT && DB.hmi1.mode.hide);

    _GUI_ClearRect(&(RECT.report.mode));
    if (!tmp->flag.mode.report) {
      GUI_SetFont(&GUI_FontSquare721_BT14);
      sprintf(str, "%s", COL.report.mode[DB.hmi1.mode.report.sel]);
      GUI_DispStringInRectWrap(str, &(RECT.report.mode), GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
    }
  }

  // Mode Report Value
  if (tmp->init
      || tmp->db.hmi1.mode.report.val != DB.hmi1.mode.report.val) {
    tmp->db.hmi1.mode.report.val = DB.hmi1.mode.report.val;

    GUI_SetFont(&GUI_FontSquare721_BT17);
    sprintf(str, "%02u", DB.hmi1.mode.report.val);
    GUI_DispStringInRectWrap(str, &(RECT.report.value), GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
  }
}

void RIGHT_ModeDrive(latch_t *tmp) {
  char str[20];

  if (tmp->init
      || tmp->db.hmi1.mode.drive != DB.hmi1.mode.drive
      || tmp->flag.mode.drive != (DB.hmi1.mode.sel == SW_M_DRIVE && DB.hmi1.mode.hide)) {
    tmp->db.hmi1.mode.drive = DB.hmi1.mode.drive;
    tmp->flag.mode.drive = (DB.hmi1.mode.sel == SW_M_DRIVE && DB.hmi1.mode.hide);

    if (!tmp->flag.mode.drive) {
      // if reverse, change color
      if (DB.hmi1.mode.drive == SW_M_DRIVE_R) {
        GUI_SetColor(0xFFFF8000);
      }
      GUI_SetFont(&GUI_FontSquare721_Cn_BT62);
      sprintf(str, "%c", COL.drive.mode[DB.hmi1.mode.drive]);
      GUI_DispStringInRectWrap(str, &(RECT.drive), GUI_TA_VCENTER | GUI_TA_HCENTER, GUI_WRAPMODE_NONE);
    } else {
      // hide
      _GUI_ClearRect(&(RECT.drive));
    }
  }
}
#endif
