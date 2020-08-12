#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
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

static uint8_t indicatorItem = 0;
	
Model::Model() 
	: modelListener(0),	ticker(0)
{

}

void Model::tick()
{
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
		modelListener->indicatorChanged(indicatorItem);

        // sein
        HMI1.d.status.sein_left =!HMI1.d.status.sein_left;
        HMI1.d.status.sein_right = !HMI1.d.status.sein_right;
		modelListener->seinChanged(1, HMI1.d.status.sein_left);
		modelListener->seinChanged(0, HMI1.d.status.sein_right);

        // mode
		// if(HMI1.d.mode.val[SW_M_DRIVE] > SW_M_DRIVE_MAX) {
			// HMI1.d.mode.val[SW_M_DRIVE] = 0;
		// } else {
			// HMI1.d.mode.val[SW_M_DRIVE]++;
		// }
		HMI1.d.mode.val[SW_M_DRIVE] = rand() % (SW_M_DRIVE_MAX + 1);
		modelListener->driveModeChanged(HMI1.d.mode.val[SW_M_DRIVE]);

		// if(HMI1.d.mode.val[SW_M_TRIP] == SW_M_TRIP_MAX) {
			// HMI1.d.mode.val[SW_M_TRIP] = 0;
		// } else {
			// HMI1.d.mode.val[SW_M_TRIP]++;
		// }
		HMI1.d.mode.val[SW_M_TRIP] = rand() % (SW_M_TRIP_MAX + 1);
		modelListener->tripModeChanged(HMI1.d.mode.val[SW_M_TRIP]);

		// if(HMI1.d.mode.val[SW_M_REPORT] == SW_M_REPORT_MAX) {
			// HMI1.d.mode.val[SW_M_REPORT] = 0;
		// } else {
			// HMI1.d.mode.val[SW_M_REPORT]++;
		// }
		HMI1.d.mode.val[SW_M_REPORT] = rand() % (SW_M_REPORT_MAX + 1);
		modelListener->reportModeChanged(HMI1.d.mode.val[SW_M_REPORT]);
    }
	
    if(ticker % 50 == 0) {
        if(BMS.d.soc > 99) {
            BMS.d.soc = 0;
        } else {
            BMS.d.soc++;
        }
		modelListener->batteryChanged(BMS.d.soc);
    }
	
    if(ticker % 30 == 0) {
        if(VCU.d.signal > 99) {
            VCU.d.signal = 0;
        } else {
            VCU.d.signal++;
        }
		modelListener->signalChanged(VCU.d.signal);
    }
	
    if(ticker % 20 == 0) {
        if(HMI1.d.mode.report >= 0xFF) {
            HMI1.d.mode.report = 0;
        } else {
            HMI1.d.mode.report++;
        }
		modelListener->reportValueChanged(HMI1.d.mode.report);
    }
	
    if(ticker % 10 == 0) {
        if(HMI1.d.mode.trip > 999999) {
            HMI1.d.mode.trip = 0;
        } else {
            HMI1.d.mode.trip++;
        }
		modelListener->tripValueChanged(HMI1.d.mode.trip);
    }

    if(ticker % 1 == 0) {
        if(VCU.d.speed >= MCU_SPEED_MAX) {
            VCU.d.speed = 0;
        } else {
            VCU.d.speed++;
        }
        MCU.d.rpm = VCU.d.speed * MCU_RPM_MAX / MCU_SPEED_MAX;
		
		modelListener->speedChanged(VCU.d.speed);
		modelListener->engineRotationChanged(MCU.d.rpm);
    }	
}
