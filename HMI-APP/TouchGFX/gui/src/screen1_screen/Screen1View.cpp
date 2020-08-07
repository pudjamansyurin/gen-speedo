#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"

#include <stdlib.h>
#ifndef SIMULATOR
#include "Nodes/VCU.h"
#include "Nodes/HMI1.h"
#include "Nodes/BMS.h"
#include "Nodes/MCU.h"

extern vcu_t VCU;
extern hmi1_t HMI1;
extern bms_t BMS;
extern mcu_t MCU;
#else
vcu_t VCU;
bms_t BMS;
mcu_t MCU;
hmi1_t HMI1;
#endif
text_database_t TDB;

Screen1View::Screen1View() :
        ticker(0),
		indicatorItem(0)
{
	TDB.drive.color[0] = Color::getColorFrom24BitRGB(255, 255, 0);
	TDB.drive.color[1] = Color::getColorFrom24BitRGB(0, 255, 0);
	TDB.drive.color[2] = Color::getColorFrom24BitRGB(255, 0, 0);
	TDB.drive.color[3] = Color::getColorFrom24BitRGB(0, 255, 255);

	Unicode::strncpy(TDB.drive.mode[0], "ECONOMIC", DRIVEMODE_SIZE);
	Unicode::strncpy(TDB.drive.mode[1], "STANDARD", DRIVEMODE_SIZE);
	Unicode::strncpy(TDB.drive.mode[2], "SPORT", DRIVEMODE_SIZE);
	Unicode::strncpy(TDB.drive.mode[3], "PERFORMANCE", DRIVEMODE_SIZE);

	Unicode::strncpy(TDB.trip.mode[0], "TRIP A", TRIPMODE_SIZE);
	Unicode::strncpy(TDB.trip.mode[1], "TRIP B", TRIPMODE_SIZE);
	Unicode::strncpy(TDB.trip.mode[2], "ODO", TRIPMODE_SIZE);

	Unicode::strncpy(TDB.report.mode[0], "RANGE", REPORTMODE_SIZE);
	Unicode::strncpy(TDB.report.mode[1], "AVG", REPORTMODE_SIZE);

	Unicode::strncpy(TDB.report.unit[0], "KM", REPORTVALUE_SIZE);
	Unicode::strncpy(TDB.report.unit[1], "KM/KWH", REPORTVALUE_SIZE);

	// indicator list
	indicatorList[0] = BITMAP_MAINREVERSE_ID;
	indicatorList[1] = BITMAP_MAINGO_ID;
	indicatorList[2] = BITMAP_BATTERYDRAINOUT_ID;
	indicatorList[3] = BITMAP_BRAKESYSTEMALERT_ID;
	indicatorList[4] = BITMAP_COOLANTTEMPERATUREWARNING_ID;
	indicatorList[5] = BITMAP_ELECTRONICERRORMESSAGE_ID;
	indicatorList[6] = BITMAP_FINGERSCANLOGINSTATUS_ID;
	indicatorList[7] = BITMAP_HIGHBEAMACTIVATED_ID;
	indicatorList[8] = BITMAP_KEYLESSIGNITIONKEYDETECTION_ID;
	indicatorList[9] = BITMAP_SMARTPHONEMIRRORINGSTATUS_ID;
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::scrollWheelUpdateItem(imageContainer& item, int16_t itemIndex)
{
    item.updateImage(Bitmap(indicatorList[itemIndex]));
}

// void Screen1View::scrollWheelUpdateCenterItem(centerContainer& item, int16_t itemIndex)
// {
// }

void Screen1View::handleTickEvent() {
    ticker++;

    if(ticker % 60 == 0) {
        // indicator
        HMI1.d.status.abs = rand() & 1;
        HMI1.d.status.mirror = rand() & 1;
        HMI1.d.status.lamp = rand() & 1;
        HMI1.d.status.warning = rand() & 1;
        HMI1.d.status.overheat = rand() & 1;
        HMI1.d.status.finger = rand() & 1;
        HMI1.d.status.keyless = rand() & 1;
        HMI1.d.status.daylight = rand() & 1;
        HMI1.d.mode.reverse = rand() & 1;

        if(indicatorItem >= INDICATOR_MAX) {
            indicatorItem = 0;
        } else  {
            indicatorItem++;
        }
		// indicatorItem = rand() % INDICATOR_MAX;

		scrollWheel.animateToItem(indicatorItem, 50);
		scrollWheel.invalidate();

        // sein
        HMI1.d.status.sein_left =!HMI1.d.status.sein_left;
        HMI1.d.status.sein_right = !HMI1.d.status.sein_right;

		if(HMI1.d.status.sein_left) {
			if(!seinLeft.isVisible()){
				seinLeft.setVisible(true);
				seinLeft.startMoveAnimation(0, 0, 20, EasingEquations::linearEaseOut, EasingEquations::linearEaseOut);
				seinLeft.invalidate();
			}
		} else {
			if(seinLeft.isVisible()){
				seinLeft.setVisible(false);
				seinLeft.setXY(80, 0);
				seinLeft.invalidate();
			}
		}

		if(HMI1.d.status.sein_right) {
			if(!seinRight.isVisible()){
				seinRight.setVisible(true);
				seinRight.startMoveAnimation(0, 0, 20, EasingEquations::linearEaseOut, EasingEquations::linearEaseOut);
				seinRight.invalidate();
			}
		} else {
			if(seinRight.isVisible()){
				seinRight.setVisible(false);
				seinRight.setXY(-80, 0);
				seinRight.invalidate();
			}
		}

        // mode
		if(HMI1.d.mode.val[SW_M_DRIVE] == SW_M_DRIVE_MAX) {
			HMI1.d.mode.val[SW_M_DRIVE] = 0;
		} else {
			HMI1.d.mode.val[SW_M_DRIVE]++;
		}
        Unicode::snprintf(driveModeBuffer, DRIVEMODE_SIZE, "%s",
			TDB.drive.mode[HMI1.d.mode.val[SW_M_DRIVE]]);
		driveMode.setColor(TDB.drive.color[HMI1.d.mode.val[SW_M_DRIVE]]);
        driveMode.invalidate();

		if(HMI1.d.mode.val[SW_M_TRIP] == SW_M_TRIP_MAX) {
			HMI1.d.mode.val[SW_M_TRIP] = 0;
		} else {
			HMI1.d.mode.val[SW_M_TRIP]++;
		}
        Unicode::snprintf(tripModeBuffer, TRIPMODE_SIZE, "%s",
			TDB.trip.mode[HMI1.d.mode.val[SW_M_TRIP]]);
        tripMode.invalidate();

		if(HMI1.d.mode.val[SW_M_REPORT] == SW_M_REPORT_MAX) {
			HMI1.d.mode.val[SW_M_REPORT] = 0;
		} else {
			HMI1.d.mode.val[SW_M_REPORT]++;
		}
        Unicode::snprintf(reportModeBuffer, REPORTMODE_SIZE, "%s",
			TDB.report.mode[HMI1.d.mode.val[SW_M_REPORT]]);
        reportMode.invalidate();
    }
    if(ticker % 50 == 0) {
        if(BMS.d.soc > 99) {
            BMS.d.soc = 0;
        } else  {
            BMS.d.soc++;
        }

        Unicode::snprintf(batteryValueBuffer, BATTERYVALUE_SIZE, "%3d", BMS.d.soc);
        batteryValue.invalidate();
    }
    if(ticker % 30 == 0) {
        if(VCU.d.signal > 99) {
            VCU.d.signal = 0;
        } else  {
            VCU.d.signal++;
        }

        Unicode::snprintf(signalValueBuffer, SIGNALVALUE_SIZE, "%3d", VCU.d.signal);
        signalValue.invalidate();
    }
    if(ticker % 20 == 0) {
        if(HMI1.d.mode.report >= 0xFF) {
            HMI1.d.mode.report = 0;
        } else  {
            HMI1.d.mode.report++;
        }

        Unicode::snprintf(reportValueBuffer, REPORTVALUE_SIZE, "%03d %s",
			HMI1.d.mode.report,
			TDB.report.unit[HMI1.d.mode.val[SW_M_REPORT]]);
        reportValue.invalidate();
    }
    if(ticker % 10 == 0) {
        if(HMI1.d.mode.trip > 999999) {
            HMI1.d.mode.trip = 0;
        } else  {
            HMI1.d.mode.trip++;
        }

        Unicode::snprintf(tripValueBuffer, TRIPVALUE_SIZE, "%06d", HMI1.d.mode.trip);
        tripValue.invalidate();
    }

    if(ticker % 1 == 0) {
        if(VCU.d.speed >= MCU_SPEED_MAX) {
            VCU.d.speed = 0;
        } else  {
            VCU.d.speed++;
        }
        MCU.d.rpm = VCU.d.speed * MCU_RPM_MAX / MCU_SPEED_MAX;

		speedProgress.setValue(VCU.d.speed * 100 / 150);
		speedProgress.invalidate();

		engineProgress.setValue(MCU.d.rpm * 100 / MCU_RPM_MAX);
		engineProgress.invalidate();
    }
}
