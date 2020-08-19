#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <stdlib.h>

#if !defined(SIMULATOR) || defined(LCD_TESTING)
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

Model::Model()
    : modelListener(0), ticker(0), indicator(1), indicators {0}
{
#ifdef SIMULATOR
	generateRandomIndicators();

	HMI1.d.mode.sel = SW_M_DRIVE;
	HMI1.d.mode.hide = 0;

	HMI1.d.mode.val[SW_M_TRIP] = SW_M_TRIP_ODO;
	HMI1.d.mode.val[SW_M_DRIVE] = SW_M_DRIVE_STANDARD;
	HMI1.d.mode.val[SW_M_REPORT] = SW_M_REPORT_RANGE;
#endif
}

void Model::tick()
{
    ticker++;

#ifdef SIMULATOR
    if (ticker % 1 == 0) {
        if (VCU.d.speed >= MCU_SPEED_MAX) {
            VCU.d.speed = 0;
        } else {
            VCU.d.speed += 5;
        }
        MCU.d.rpm = VCU.d.speed * MCU_RPM_MAX / MCU_SPEED_MAX;
    }

    if (ticker % 10 == 0) {
        if (HMI1.d.mode.trip >= 999999) {
            HMI1.d.mode.trip = 0;
        } else {
            HMI1.d.mode.trip++;
        }
    }

    if (ticker % 20 == 0) {
        if (HMI1.d.mode.report >= 255) {
            HMI1.d.mode.report = 0;
        } else {
            HMI1.d.mode.report++;
        }

		HMI1.d.mode.hide = !HMI1.d.mode.hide;
    }

    if(ticker % 30 == 0) {
        if (VCU.d.signal >= 100) {
            VCU.d.signal = 0;
        } else {
            VCU.d.signal++;
        }

        HMI1.d.sein.left =!HMI1.d.sein.left;
        HMI1.d.sein.right = !HMI1.d.sein.right;
    }

    if (ticker % 50 == 0) {
        if (BMS.d.soc >= 100) {
            BMS.d.soc = 0;
        } else {
            BMS.d.soc++;
        }
    }

    if (ticker % 60 == 0) {
		if (HMI1.d.mode.val[SW_M_TRIP] >= SW_M_TRIP_MAX) {
			HMI1.d.mode.val[SW_M_TRIP] = 0;
		} else {
			HMI1.d.mode.val[SW_M_TRIP]++;
		}
		if (HMI1.d.mode.val[SW_M_DRIVE] >= SW_M_DRIVE_MAX) {
			HMI1.d.mode.val[SW_M_DRIVE] = 0;
		} else {
			HMI1.d.mode.val[SW_M_DRIVE]++;
		}
		if (HMI1.d.mode.val[SW_M_REPORT] >= SW_M_REPORT_MAX) {
			HMI1.d.mode.val[SW_M_REPORT] = 0;
		} else {
			HMI1.d.mode.val[SW_M_REPORT]++;
		}
    }

    if (ticker % (60*2) == 0) {
		 if (indicator >= INDICATOR_MAX) {
			 indicator = 0;
		 } else {
			 indicator++;
		 }
        // swipeIndicator();
	}

    if (ticker % (60*3) == 0) {
		if (HMI1.d.mode.sel >= SW_M_MAX) {
			HMI1.d.mode.sel = 0;
		} else {
			HMI1.d.mode.sel++;
		}
	}

    if (ticker % (60*60) == 0) {
		generateRandomIndicators();
    }
#endif

    // write to LCD
    modelListener->setSpeed(VCU.d.speed);
    modelListener->setEngineRotation(MCU.d.rpm);

    modelListener->setTripValue(HMI1.d.mode.trip);
    modelListener->setReportValue(HMI1.d.mode.report);

    modelListener->setSignal(VCU.d.signal);
    modelListener->setBattery(BMS.d.soc);

    modelListener->setSein(1, HMI1.d.sein.left);
    modelListener->setSein(0, HMI1.d.sein.right);

    modelListener->setIndicator(indicator);

	modelListener->setModeSelector(HMI1.d.mode.sel);
	modelListener->setModeVisible(!HMI1.d.mode.hide);

	switch (HMI1.d.mode.sel) {
		case SW_M_TRIP :
			modelListener->setTripMode(HMI1.d.mode.val[SW_M_TRIP]);
			break;
		case SW_M_DRIVE:
			modelListener->setDriveMode(HMI1.d.mode.val[SW_M_DRIVE]);
			break;
		case SW_M_REPORT:
			modelListener->setReportMode(HMI1.d.mode.val[SW_M_REPORT]);
			break;
		default:
			break;
	}
}

uint8_t Model::readCurrentIndicator()
{
    return indicator;
}

uint8_t Model::readIndicatorState(uint8_t index)
{
    return indicators[index];
}

void Model::generateRandomIndicators()
{
	HMI1.d.status.abs = rand() & 1;
	HMI1.d.status.mirroring = rand() & 1;
	HMI1.d.status.lamp = rand() & 1;
	HMI1.d.status.warning = rand() & 1;
	HMI1.d.status.overheat = rand() & 1;
	HMI1.d.status.finger = rand() & 1;
	HMI1.d.status.keyless = rand() & 1;
	HMI1.d.status.daylight = rand() & 1;
	HMI1.d.mode.reverse = rand() & 1;
}

void Model::reloadIndicators()
{
	uint8_t errors = 0;

    indicators[INDICATOR_ABS] = HMI1.d.status.abs;
    indicators[INDICATOR_MIRRORING] = HMI1.d.status.mirroring;
    indicators[INDICATOR_LAMP] = HMI1.d.status.lamp;
    indicators[INDICATOR_WARNING] = HMI1.d.status.warning;
    indicators[INDICATOR_OVERHEAT] = HMI1.d.status.overheat;
    indicators[INDICATOR_FINGER] = HMI1.d.status.finger;
    indicators[INDICATOR_KEYLESS] = HMI1.d.status.keyless;
    indicators[INDICATOR_LOWBAT] = BMS.d.soc < 20;

	for (uint8_t i=INDICATOR_GO; i<INDICATOR_MAX; ++i) {
		if (indicators[i]) {
			errors = 1;
			break;
		}
	}

    indicators[INDICATOR_REVERSE] = HMI1.d.mode.reverse;
    indicators[INDICATOR_GO] = !HMI1.d.mode.reverse && !errors;
}

void Model::swipeIndicator()
{
    uint8_t i, found = 0;

    // reload data
	reloadIndicators();

    // current -> up
    for (i = indicator+1; i <= INDICATOR_MAX; i++) {
        if (indicators[i]) {
            found = 1;
            indicator = i;
            break;
        }
    }
    // down -> current
    if (!found) {
        for (i = 0; i <= indicator; i++) {
            if (indicators[i]) {
                found = 1;
                indicator = i;
                break;
            }
        }
    }
    // fallback
    if (!found) {
        indicator = 1;
    }
}

