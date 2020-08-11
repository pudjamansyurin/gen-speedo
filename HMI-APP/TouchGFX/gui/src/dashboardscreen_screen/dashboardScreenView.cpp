#include <gui/dashboardscreen_screen/dashboardScreenView.hpp>

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

dashboardScreenView::dashboardScreenView() :
	ticker(0),
	indicatorItem(0)
{
	
}

void dashboardScreenView::setupScreen()
{
    dashboardScreenViewBase::setupScreen();
}

void dashboardScreenView::tearDownScreen()
{
    dashboardScreenViewBase::tearDownScreen();
}

void dashboardScreenView::driveWheelUpdateItem(driveWheelContainer& item, int16_t itemIndex)
{
    item.updateText(itemIndex);
}

void dashboardScreenView::indicatorWheelUpdateItem(indicatorWheelContainer& item, int16_t itemIndex)
{
    item.updateImage(itemIndex);
}

void dashboardScreenView::tripWheelUpdateItem(tripWheelContainer& item, int16_t itemIndex) 
{
    item.updateText(itemIndex);
}

void dashboardScreenView::reportWheelUpdateItem(reportWheelContainer& item, int16_t itemIndex)
{
    item.updateText(itemIndex);
}

void dashboardScreenView::handleTickEvent() {
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

        // if(indicatorItem >= INDICATOR_MAX) {
            // indicatorItem = 0;
        // } else  {
            // indicatorItem++;
        // }
		indicatorItem = rand() % (INDICATOR_MAX + 1);
		indicatorWheel.animateToItem(indicatorItem, 0);
		indicatorWheel.invalidate();

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
		// if(HMI1.d.mode.val[SW_M_DRIVE] > SW_M_DRIVE_MAX) {
			// HMI1.d.mode.val[SW_M_DRIVE] = 0;
		// } else {
			// HMI1.d.mode.val[SW_M_DRIVE]++;
		// }
		HMI1.d.mode.val[SW_M_DRIVE] = rand() % (SW_M_DRIVE_MAX + 1);
		driveWheel.animateToItem(HMI1.d.mode.val[SW_M_DRIVE], 0);
		driveWheel.invalidate();


		// if(HMI1.d.mode.val[SW_M_TRIP] == SW_M_TRIP_MAX) {
			// HMI1.d.mode.val[SW_M_TRIP] = 0;
		// } else {
			// HMI1.d.mode.val[SW_M_TRIP]++;
		// }
		HMI1.d.mode.val[SW_M_TRIP] = rand() % (SW_M_TRIP_MAX + 1);
		tripWheel.animateToItem(HMI1.d.mode.val[SW_M_TRIP], 0);
		tripWheel.invalidate();

		// if(HMI1.d.mode.val[SW_M_REPORT] == SW_M_REPORT_MAX) {
			// HMI1.d.mode.val[SW_M_REPORT] = 0;
		// } else {
			// HMI1.d.mode.val[SW_M_REPORT]++;
		// }
		HMI1.d.mode.val[SW_M_REPORT] = rand() % (SW_M_REPORT_MAX + 1);
		reportValue.setX(!HMI1.d.mode.val[SW_M_REPORT] ? 423 : 362);
		reportValue.invalidate();
		reportWheel.animateToItem(HMI1.d.mode.val[SW_M_REPORT]);
		reportWheel.invalidate();
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
		
		Unicode::snprintf(reportValueBuffer, REPORTVALUE_SIZE, "%03d", HMI1.d.mode.report);
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
