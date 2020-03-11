/*
 * _gui.c
 *
 *  Created on: Oct 21, 2019
 *      Author: Puja
 */

/* Includes ------------------------------------------------------------------*/
#if !USE_HMI_LEFT
#include "Square721_BT10.c"
#include "Square721_BT14.c"
#include "Square721_BT17.c"
#include "Square721_BT31.c"
#include "Square721_BT60.c"
#include "Square721_Cn_BT62.c"
#endif
#include "Square721_BT23.c"
#include "_guiapp.h"

/* External variable */
extern IWDG_HandleTypeDef hiwdg;
extern db_t DB;
extern guiapp_t GAPP;

/* Functions prototypes --------------------------------------------------------*/
static void RunBootAnimation(void);
static void BootOverlay(guiapp_t *GA);

/* Main task ------------------------------------------------------------------*/
void GUI_MainTask(void) {
  /* USER CODE BEGIN GUI_MainTask */
  latch_t TMP = {0};

  char str[20];
  uint8_t init = 1;
  uint32_t notifValue;
  BaseType_t xResult;

#if USE_HMI_LEFT
const uint8_t x = 58, y = 161, r = 123, h = 7, max = 112;
  GUI_RECT pRect_SubTrip = { 159, 83, 159 + 64, 83 + 24 };
  GUI_RECT pRect_TotalTrip = { 159, 106, 159 + 64, 106 + 24 };
  // create MEMDEV on layer 1
  GUI_SelectLayer(1);
  GUI_MEMDEV_Handle hMem = GUI_MEMDEV_Create(
    x, 
    y - r, 
    x + r + (r * cos(_D2R(max + 180))) + 5 - x + 25, 
    y + h + 5 - (y - r)
  );
#else
  int8_t RM_XO = -10;
  GUI_RECT pRect_Speed = { 83, 79, 85 + 102, 79 + 50 };
  GUI_RECT pRect_Battery = { 227, 164, 227 + 35, 164 + 28 };
  GUI_RECT pRect_Battery_Unit = { 266, 170, 266 + 17, 170 + 17 };
  GUI_RECT pRect_Signal = { 122, 50, 122 + 65, 50 + 10 };
  GUI_RECT pRect_Drive = { 126, 145, 126 + 26, 145 + 40 };
  GUI_RECT pRect_Report_Mode = { 174 + RM_XO, 191, 174 + 50 + RM_XO, 191 + 13 };
  GUI_RECT pRect_Report_Value = { 228 + RM_XO, 190, 228 + 20 + RM_XO, 190 + 15 };
  GUI_RECT pRect_Report_Unit = { 251 + RM_XO, 194, 251 + 28 + RM_XO, 194 + 10 };

  const char Report_Mode[2][8] = { "Range", "Average" };
  const char Drive_Mode[4] = { 'E', 'S', 'P', 'R' };
  const char Report_Unit[2][7] = { "KM", "KM/KWh" };
#endif

  // Set overlay on all indicator on boot
  BootOverlay(&GAPP);

  // Run booting animation on start
  RunBootAnimation();

  // Draw the layer 0 background
  GUI_SelectLayer(0);
  GUI_DrawBitmap(GAPP.background, 0, 0);
  GUI_Delay(500);

  // Make layer 1 transparent
  GUI_SelectLayer(1);
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_Clear();
  GUI_SetBkColor(GUI_BLACK);

  while (1) {
    // Feed the dog
    HAL_IWDG_Refresh(&hiwdg);

    if (!init) {
      // check if has new can message
      xResult = xTaskNotifyWait(0x00, ULONG_MAX, &notifValue, pdMS_TO_TICKS(500));
    }

    // if not receive any CAN message
    if (xResult == pdFALSE) {
      init = 1;
    }

    // init hook
    if (init) {
      // reset data to default
      Reset_Database();
      // set back-light ON
      _SetBacklight(1);
    }

#if USE_HMI_LEFT
    // Sein Left
    if (TMP.db.hmi1.status.sein_left != DB.hmi1.status.sein_left) {
      TMP.db.hmi1.status.sein_left = DB.hmi1.status.sein_left;
      LEFT_Sein(DB.hmi1.status.sein_left);
    }

    // Finger
    if (init || TMP.db.hmi1.status.finger != DB.hmi1.status.finger) {
      TMP.db.hmi1.status.finger = DB.hmi1.status.finger;
      LEFT_Finger(DB.hmi1.status.finger);
    }

    // Mirror
    if (init || TMP.db.hmi1.status.mirror != DB.hmi1.status.mirror) {
      TMP.db.hmi1.status.mirror = DB.hmi1.status.mirror;
      LEFT_Mirror(DB.hmi1.status.mirror);
    }

    // Others
    if (init
        || TMP.db.hmi1.mode.trip.sel != DB.hmi1.mode.trip.sel
        || TMP.db.hmi1.mode.trip.val != DB.hmi1.mode.trip.val
        || TMP.db.vcu.odometer != DB.vcu.odometer
        || TMP.db.mcu.rpm != DB.mcu.rpm
        || TMP.db.hmi1.status.keyless != DB.hmi1.status.keyless
        || TMP.flag.mode.trip != (DB.hmi1.mode.sel == SW_M_TRIP && DB.hmi1.mode.hide)) {

      // Set Color
      GUI_SetColor(0xFFC0C0C0);

      // Clear Left HMI
      GUI_MEMDEV_Select(hMem);
      GUI_DrawBitmapEx(GAPP.background, x, y - r, x, y - r, 1000, 1000);

      // Mode Trip
      {
        TMP.db.hmi1.mode.trip.sel = DB.hmi1.mode.trip.sel;
        TMP.flag.mode.trip = (DB.hmi1.mode.sel == SW_M_TRIP && DB.hmi1.mode.hide);

        if (!TMP.flag.mode.trip) {
          // Mode Trip Label
          LEFT_Trip(DB.hmi1.mode.trip.sel);
        }

        // Mode Trip Value
        TMP.db.hmi1.mode.trip.val = DB.hmi1.mode.trip.val;
        GUI_SetFont(&GUI_FontSquare721_BT23);
        sprintf(str, "%05u", (unsigned int) DB.hmi1.mode.trip.val);
        GUI_DispStringInRectWrap(str, &pRect_SubTrip, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
      }

      // Odometer
      TMP.db.vcu.odometer = DB.vcu.odometer;
      GUI_SetFont(&GUI_FontSquare721_BT23);
      sprintf(str, "%05u", (unsigned int) DB.vcu.odometer);
      GUI_DispStringInRectWrap(str, &pRect_TotalTrip, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);

      // Keyless
      TMP.db.hmi1.status.keyless = DB.hmi1.status.keyless;
      LEFT_Keyless(DB.hmi1.status.keyless);

      // RPM Needle
      TMP.db.mcu.rpm = DB.mcu.rpm;
      LEFT_Needle(DB.mcu.rpm <= MCU_RPM_MAX ? DB.mcu.rpm * max / MCU_RPM_MAX : max, x, y, r, h, max);

      // Print result to LCD
      GUI_MEMDEV_Select(0);
      GUI_MEMDEV_CopyToLCD(hMem);
    }

#else
    // Sein Right
    if (TMP.db.hmi1.status.sein_right != DB.hmi1.status.sein_right) {
      TMP.db.hmi1.status.sein_right = DB.hmi1.status.sein_right;
      RIGHT_Sein(DB.hmi1.status.sein_right);
    }

    // Warning
    if (init || TMP.db.hmi1.status.warning != DB.hmi1.status.warning) {
      TMP.db.hmi1.status.warning = DB.hmi1.status.warning;
      RIGHT_Warning(DB.hmi1.status.warning);
    }

    // ABS
    if (init || TMP.db.hmi1.status.abs != DB.hmi1.status.abs) {
      TMP.db.hmi1.status.abs = DB.hmi1.status.abs;
      RIGHT_ABS(DB.hmi1.status.abs);
    }

    // Temperature Indicator
    if (init || TMP.db.hmi1.status.temperature != DB.hmi1.status.temperature) {
      TMP.db.hmi1.status.temperature = DB.hmi1.status.temperature;
      RIGHT_Temperature(DB.hmi1.status.temperature);
    }

    // Lamp
    if (init || TMP.db.hmi1.status.lamp != DB.hmi1.status.lamp) {
      TMP.db.hmi1.status.lamp = DB.hmi1.status.lamp;
      RIGHT_Lamp(DB.hmi1.status.lamp);
    }

    // Set Color
    GUI_SetColor(0xFFC0C0C0);

    // Speed
    if (init || TMP.db.vcu.speed != DB.vcu.speed) {
      TMP.db.vcu.speed = DB.vcu.speed;

      GUI_SetFont(&GUI_FontSquare721_BT60);
      sprintf(str, "%03u", DB.vcu.speed);
      GUI_DispStringInRectWrap(str, &pRect_Speed, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
    }

    // Battery Percentage
    {
      if (init || TMP.db.bms.soc != DB.bms.soc) {
        TMP.db.bms.soc = DB.bms.soc;

        // Battery Value
        GUI_SetFont(&GUI_FontSquare721_BT31);
        sprintf(str, "%02u", DB.bms.soc);
        GUI_DispStringInRectWrap(str, &pRect_Battery, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
      }

      // Detect trigger event
      if (DB.bms.soc <= 20) {
        if (!TMP.flag.soc.low) {
          TMP.flag.soc.low = 1;
          TMP.flag.battery.low = 0;
          TMP.flag.soc.update = 1;
        } else if ((osKernelSysTick() - TMP.flag.battery.tick) >= pdMS_TO_TICKS(500)) {
          TMP.flag.battery.tick = osKernelSysTick();
          TMP.flag.battery.low = !TMP.flag.battery.low;
          TMP.flag.soc.update = 1;
        }
      } else if (DB.bms.soc > 20 && TMP.flag.soc.low) {
        TMP.flag.soc.low = 0;
        TMP.flag.battery.low = 0;
        TMP.flag.soc.update = 1;
      }

      // Battery Icon & Unit
      if (init || TMP.flag.soc.update) {
        TMP.flag.soc.update = 0;

        // Battery Icon
        RIGHT_Battery(TMP.flag.battery.low ? -1 : DB.bms.soc);

        // Battery Unit
        if (DB.bms.soc <= 20) {
          GUI_SetColor(0xFFE62129);
        }
        GUI_ClearRect(pRect_Battery_Unit.x0, pRect_Battery_Unit.y0, pRect_Battery_Unit.x1, pRect_Battery_Unit.y1);
        GUI_SetFont(&GUI_FontSquare721_BT17);
        sprintf(str, "%c", '%');
        GUI_DispStringInRectWrap(str, &pRect_Battery_Unit, GUI_TA_BOTTOM | GUI_TA_LEFT, GUI_WRAPMODE_NONE);
        GUI_SetColor(0xFFC0C0C0);
      }
    }

    // Signal Percentage
    if (init || TMP.db.vcu.signal != DB.vcu.signal) {
      TMP.db.vcu.signal = DB.vcu.signal;

      // fill all black
      GUI_SetBkColor(GUI_BLACK);
      GUI_ClearRect(pRect_Signal.x0, pRect_Signal.y0, pRect_Signal.x1, pRect_Signal.y1);
      // clear some transparent
      GUI_SetBkColor(GUI_TRANSPARENT);
      GUI_ClearRect(
          pRect_Signal.x0,
          pRect_Signal.y0,
          pRect_Signal.x0 + (DB.vcu.signal * (pRect_Signal.x1 - pRect_Signal.x0) / 100),
          pRect_Signal.y1
      );
      // reset the bg color
      GUI_SetBkColor(GUI_BLACK);
    }

    // Mode Report
    {
      // Mode Report Unit
      if (init || TMP.db.hmi1.mode.report.sel != DB.hmi1.mode.report.sel) {
        GUI_ClearRect(pRect_Report_Unit.x0, pRect_Report_Unit.y0, pRect_Report_Unit.x1, pRect_Report_Unit.y1);
        GUI_SetFont(&GUI_FontSquare721_BT10);
        sprintf(str, "%s", Report_Unit[DB.hmi1.mode.report.sel]);
        GUI_DispStringInRectWrap(str, &pRect_Report_Unit, GUI_TA_BOTTOM | GUI_TA_LEFT, GUI_WRAPMODE_NONE);
      }

      // Mode Report Label
      if (init || TMP.db.hmi1.mode.report.sel != DB.hmi1.mode.report.sel
          || TMP.flag.mode.report != (DB.hmi1.mode.sel == SW_M_REPORT && DB.hmi1.mode.hide)) {
        TMP.db.hmi1.mode.report.sel = DB.hmi1.mode.report.sel;
        TMP.flag.mode.report = (DB.hmi1.mode.sel == SW_M_REPORT && DB.hmi1.mode.hide);

        GUI_ClearRect(pRect_Report_Mode.x0, pRect_Report_Mode.y0, pRect_Report_Mode.x1, pRect_Report_Mode.y1);
        if (!TMP.flag.mode.report) {
          GUI_SetFont(&GUI_FontSquare721_BT14);
          sprintf(str, "%s", Report_Mode[DB.hmi1.mode.report.sel]);
          GUI_DispStringInRectWrap(str, &pRect_Report_Mode, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
        }
      }

      // Mode Report Value
      if (init || TMP.db.hmi1.mode.report.val != DB.hmi1.mode.report.val) {
        TMP.db.hmi1.mode.report.val = DB.hmi1.mode.report.val;

        GUI_SetFont(&GUI_FontSquare721_BT17);
        sprintf(str, "%02u", DB.hmi1.mode.report.val);
        GUI_DispStringInRectWrap(str, &pRect_Report_Value, GUI_TA_BOTTOM | GUI_TA_RIGHT, GUI_WRAPMODE_NONE);
      }
    }

    // Mode Drive
    if (init || TMP.db.hmi1.mode.drive != DB.hmi1.mode.drive
        || TMP.flag.mode.drive != (DB.hmi1.mode.sel == SW_M_DRIVE && DB.hmi1.mode.hide)) {
      TMP.db.hmi1.mode.drive = DB.hmi1.mode.drive;
      TMP.flag.mode.drive = (DB.hmi1.mode.sel == SW_M_DRIVE && DB.hmi1.mode.hide);

      if (!TMP.flag.mode.drive) {
        // if reverse, change color
        if (DB.hmi1.mode.drive == SW_M_DRIVE_R) {
          GUI_SetColor(0xFFFF8000);
        }
        GUI_SetFont(&GUI_FontSquare721_Cn_BT62);
        sprintf(str, "%c", Drive_Mode[DB.hmi1.mode.drive]);
        GUI_DispStringInRectWrap(str, &pRect_Drive,
            GUI_TA_VCENTER | GUI_TA_HCENTER, GUI_WRAPMODE_NONE);
      } else {
        // hide
        GUI_ClearRect(pRect_Drive.x0, pRect_Drive.y0, pRect_Drive.x1, pRect_Drive.y1);
      }
    }
#endif

    init = 0;
  }
  /* USER CODE END GUI_MainTask */
}

// Functions list
static void RunBootAnimation(void) {
  // start of booting animation
  GUI_SelectLayer(1);
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  // start of circular booting animation
  GUI_SetColor(GUI_TRANSPARENT);

#if USE_HMI_LEFT
  LEFT_Animation();
#else
  RIGHT_Animation();
#endif
  // end of booting animation
}

static void BootOverlay(guiapp_t *GA) {
  // Make layer 1 transparent
  GUI_SelectLayer(1);
  GUI_SetBkColor(GUI_TRANSPARENT);
  GUI_Clear();

  // Give overlay on indicators at layer 1
  GUI_SelectLayer(0);
  GUI_DrawBitmap(GA->background, 0, 0);

  // overlay for first booting
  GUI_SetColor(GUI_BLACK);
  GUI_FillPolygon(GA->overlay.points, GA->overlay.count, 0, 0);
}
/*************************** End of file ****************************/
