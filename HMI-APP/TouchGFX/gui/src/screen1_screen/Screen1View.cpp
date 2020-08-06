#include <gui/screen1_screen/Screen1View.hpp>

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

Screen1View::Screen1View() :
        ticker(0)
{	
	Unicode::strncpy(HMI1.ref.drive.mode[0], "ECONOMIC", DRIVEMODE_SIZE);
	Unicode::strncpy(HMI1.ref.drive.mode[1], "STANDARD", DRIVEMODE_SIZE);
	Unicode::strncpy(HMI1.ref.drive.mode[2], "SPORT", DRIVEMODE_SIZE);
	Unicode::strncpy(HMI1.ref.drive.mode[3], "PERFORMANCE", DRIVEMODE_SIZE);
	
	Unicode::strncpy(HMI1.ref.trip.mode[0], "TRIP A", TRIPMODE_SIZE);
	Unicode::strncpy(HMI1.ref.trip.mode[1], "TRIP B", TRIPMODE_SIZE);
	Unicode::strncpy(HMI1.ref.trip.mode[2], "ODO", TRIPMODE_SIZE);
	
	Unicode::strncpy(HMI1.ref.report.mode[0], "RANGE", REPORTMODE_SIZE);
	Unicode::strncpy(HMI1.ref.report.mode[1], "AVG", REPORTMODE_SIZE);
	
	Unicode::strncpy(HMI1.ref.report.unit[0], "KM", REPORTVALUE_SIZE);
	Unicode::strncpy(HMI1.ref.report.unit[1], "KM/KWH", REPORTVALUE_SIZE);
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::handleTickEvent() {
    ticker++;

    if(ticker % 60 == 0) {
        // // indicator
        // HMI1.d.status.abs = rand() & 1;
        // HMI1.d.status.mirror = rand() & 1;
        // HMI1.d.status.lamp = rand() & 1;
        // HMI1.d.status.warning = rand() & 1;
        // HMI1.d.status.overheat = rand() & 1;
        // HMI1.d.status.finger = rand() & 1;
        // HMI1.d.status.keyless = rand() & 1;
        // HMI1.d.status.daylight = rand() & 1;

        // sein
        HMI1.d.status.sein_left = rand() & 1;
        HMI1.d.status.sein_right = rand() & 1;
        HMI1.d.mode.reverse = rand() & 1;

        seinLeft.setVisible(HMI1.d.status.sein_left);
        seinLeft.invalidate();
        seinRight.setVisible(HMI1.d.status.sein_right);
        seinRight.invalidate();

        // mode
		if(HMI1.d.mode.val[SW_M_DRIVE] == SW_M_DRIVE_MAX) {
			HMI1.d.mode.val[SW_M_DRIVE] = 0;
		} else {
			HMI1.d.mode.val[SW_M_DRIVE]++;
		}		
        Unicode::snprintf(driveModeBuffer, DRIVEMODE_SIZE, "%s", 
			HMI1.ref.drive.mode[HMI1.d.mode.val[SW_M_DRIVE]]);
        driveMode.invalidate();	
		
		if(HMI1.d.mode.val[SW_M_TRIP] == SW_M_TRIP_MAX) {
			HMI1.d.mode.val[SW_M_TRIP] = 0;
		} else {
			HMI1.d.mode.val[SW_M_TRIP]++;
		}		
        Unicode::snprintf(tripModeBuffer, TRIPMODE_SIZE, "%s", 
			HMI1.ref.trip.mode[HMI1.d.mode.val[SW_M_TRIP]]);
        tripMode.invalidate();	
		
		if(HMI1.d.mode.val[SW_M_REPORT] == SW_M_REPORT_MAX) {
			HMI1.d.mode.val[SW_M_REPORT] = 0;
		} else {
			HMI1.d.mode.val[SW_M_REPORT]++;
		}		
        Unicode::snprintf(reportModeBuffer, REPORTMODE_SIZE, "%s", 
			HMI1.ref.report.mode[HMI1.d.mode.val[SW_M_REPORT]]);
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
			HMI1.ref.report.unit[HMI1.d.mode.val[SW_M_REPORT]]);
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

    if(ticker % 40 == 0) {
        if(VCU.d.speed > 150) {
            VCU.d.speed = 0;
        } else  {
            VCU.d.speed++;
        }

        // convert Speed to RPM
        MCU.d.rpm = VCU.d.speed * MCU_RPM_MAX / MCU_SPEED_MAX;
    }
}
