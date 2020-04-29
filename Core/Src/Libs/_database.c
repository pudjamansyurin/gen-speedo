/*
 * _database.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Puja
 */
/* Includes ------------------------------------------------------------------*/
#include "_database.h"

/* Variables ------------------------------------------------------------------*/
db_t DB;

/* Functions -----------------------------------------------------------------*/
void Reset_Database(void) {
  DB.vcu.signal = 0;
  DB.vcu.speed = 0;
  DB.vcu.odometer = 0;
  DB.mcu.rpm = 0;
  DB.bms.soc = 0;
  DB.hmi1.status.abs = 0;
  DB.hmi1.status.mirror = 0;
  DB.hmi1.status.lamp = 0;
  DB.hmi1.status.warning = 1;
  DB.hmi1.status.overheat = 0;
  DB.hmi1.status.finger = 0;
  DB.hmi1.status.keyless = 0;
  DB.hmi1.status.daylight = 1;
  DB.hmi1.status.sein_left = 0;
  DB.hmi1.status.sein_right = 0;
  DB.hmi1.mode.sel = SW_M_TRIP;
  DB.hmi1.mode.hide = 0;
  DB.hmi1.mode.drive = SW_M_DRIVE_E;
  DB.hmi1.mode.trip.sel = SW_M_TRIP_A;
  DB.hmi1.mode.trip.val = 0;
  DB.hmi1.mode.report.sel = SW_M_REPORT_RANGE;
  DB.hmi1.mode.report.val = 0;
}
