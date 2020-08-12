#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <stdlib.h>

#ifndef SIMULATOR
extern "C"
{
    #include "Libs/_utils.h"
    #include "Nodes/VCU.h"
    #include "Nodes/HMI1.h"
    #include "Nodes/BMS.h"
    #include "Nodes/MCU.h"
}

extern "C" vcu_t VCU;
extern "C" hmi1_t HMI1;
extern "C" bms_t BMS;
extern "C" mcu_t MCU;
#else
vcu_t VCU;
bms_t BMS;
mcu_t MCU;
hmi1_t HMI1;
#endif

static uint8_t indicator = 1;
static uint8_t indicators[INDICATOR_MAX+1] = { 0 };

Model::Model()
	: modelListener(0),	ticker(0)
{

}

void Model::refreshIndicators()
{
    indicators[INDICATOR_REVERSE] = HMI1.d.mode.reverse;
    indicators[INDICATOR_GO] = !HMI1.d.mode.reverse;
    indicators[INDICATOR_ABS] = HMI1.d.status.abs;
    indicators[INDICATOR_MIRRORING] = HMI1.d.status.mirroring;
    indicators[INDICATOR_LAMP] = HMI1.d.status.lamp;
    indicators[INDICATOR_WARNING] = HMI1.d.status.warning;
    indicators[INDICATOR_OVERHEAT] = HMI1.d.status.overheat;
    indicators[INDICATOR_FINGER] = HMI1.d.status.finger;
    indicators[INDICATOR_KEYLESS] = HMI1.d.status.keyless;
    indicators[INDICATOR_LOWBAT] = BMS.d.soc < 20;
}

void Model::tick()
{
	ticker++;

    if (ticker % 1 == 0) {
        if (VCU.d.speed >= MCU_SPEED_MAX) {
            VCU.d.speed = 0;
        } else {
            VCU.d.speed++;
        }
        MCU.d.rpm = VCU.d.speed * MCU_RPM_MAX / MCU_SPEED_MAX;

        modelListener->speedChanged(VCU.d.speed);
        modelListener->engineRotationChanged(MCU.d.rpm);
    }

    if (ticker % 10 == 0) {
        if (HMI1.d.mode.trip > 999999) {
            HMI1.d.mode.trip = 0;
        } else {
            HMI1.d.mode.trip++;
        }
        modelListener->tripValueChanged(HMI1.d.mode.trip);
    }

    if (ticker % 20 == 0) {
        if (HMI1.d.mode.report >= 0xFF) {
            HMI1.d.mode.report = 0;
        } else {
            HMI1.d.mode.report++;
        }
        modelListener->reportValueChanged(HMI1.d.mode.report);
    }

    if(ticker % 30 == 0) {
        if (VCU.d.signal > 99) {
            VCU.d.signal = 0;
        } else {
            VCU.d.signal++;
        }
        modelListener->signalChanged(VCU.d.signal);
    }

    if (ticker % 50 == 0) {
        if (BMS.d.soc > 99) {
            BMS.d.soc = 0;
        } else {
            BMS.d.soc++;
        }
        modelListener->batteryChanged(BMS.d.soc);
    }

    if (ticker % 60 == 0) {
        // sein
        HMI1.d.sein.left =!HMI1.d.sein.left;
        HMI1.d.sein.right = !HMI1.d.sein.right;

        modelListener->seinChanged(1, HMI1.d.sein.left);
        modelListener->seinChanged(0, HMI1.d.sein.right);


        // if(HMI1.d.mode.val[SW_M_TRIP] == SW_M_TRIP_MAX) {
            // HMI1.d.mode.val[SW_M_TRIP] = 0;
        // } else {
            // HMI1.d.mode.val[SW_M_TRIP]++;
        // }
        HMI1.d.mode.val[SW_M_TRIP] = rand() % (SW_M_TRIP_MAX + 1);

        // mode
		// if(HMI1.d.mode.val[SW_M_DRIVE] > SW_M_DRIVE_MAX) {
			// HMI1.d.mode.val[SW_M_DRIVE] = 0;
		// } else {
			// HMI1.d.mode.val[SW_M_DRIVE]++;
		// }
		HMI1.d.mode.val[SW_M_DRIVE] = rand() % (SW_M_DRIVE_MAX + 1);

		// if(HMI1.d.mode.val[SW_M_REPORT] == SW_M_REPORT_MAX) {
			// HMI1.d.mode.val[SW_M_REPORT] = 0;
		// } else {
			// HMI1.d.mode.val[SW_M_REPORT]++;
		// }
		HMI1.d.mode.val[SW_M_REPORT] = rand() % (SW_M_REPORT_MAX + 1);

        modelListener->tripModeChanged(HMI1.d.mode.val[SW_M_TRIP]);
        modelListener->driveModeChanged(HMI1.d.mode.val[SW_M_DRIVE]);
		modelListener->reportModeChanged(HMI1.d.mode.val[SW_M_REPORT]);


        // if(indicator >= INDICATOR_MAX) {
            // indicator = 0;
        // } else  {
            // indicator++;
        // }
        // indicator = rand() % (INDICATOR_MAX+1);
		uint8_t found = 0;
        for (uint8_t i = indicator+1; i <= INDICATOR_MAX; i++) {
            if (indicators[i]) {
                found = 1;
                indicator = i;
                break;
            }
        }
        if (!found) {
            for (uint8_t i = 0; i <= indicator; i++) {
                if (indicators[i]) {
                    indicator = i;
                    break;
                }
            }
        }

        modelListener->indicatorChanged(indicator);
    }

    if (ticker % (60*60) == 0) {
        // indicator
        HMI1.d.mode.reverse = rand() & 1;
        HMI1.d.status.abs = rand() & 1;
        HMI1.d.status.mirroring = rand() & 1;
        HMI1.d.status.lamp = rand() & 1;
        HMI1.d.status.warning = rand() & 1;
        HMI1.d.status.overheat = rand() & 1;
        HMI1.d.status.finger = rand() & 1;
        HMI1.d.status.keyless = rand() & 1;
        HMI1.d.status.daylight = rand() & 1;

        refreshIndicators();
    }
}
