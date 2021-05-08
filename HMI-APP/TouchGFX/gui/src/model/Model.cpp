#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#if !defined(SIMULATOR)
extern "C"
{
#include "Libs/_utils.h"
#include "Nodes/VCU.h"
#include "Nodes/HMI1.h"

extern uint8_t LTDC_MEASURED_FPS;
}
#else
vcu_t VCU;
hmi1_t HMI1;
uint8_t LTDC_MEASURED_FPS = 0;
#endif

Model::Model()
:
        										modelListener(0), ticker(0), indicator(1), indicators { 0 }
{
#ifdef SIMULATOR
	setDefaultData();
	generateRandomIndicators();
#endif
}

void Model::tick()
{
	static uint8_t session = 0;

	ticker++;

#ifdef SIMULATOR
	generateRandomData();
#endif

	if (HMI1.hbar.reverse)
		indicator = INDICATOR_REVERSE;
	else if (ticker % 120 == 0)
		swipeIndicator();

	if (HMI1.hbar.listening) {
		if (ticker % 20 == 0)
			session = !session;
	} else
		session = 1;

	// write to LCD
	modelListener->setTripMode(HMI1.hbar.d.mode[HBAR_M_TRIP]);
	modelListener->setDriveMode(HMI1.hbar.d.mode[HBAR_M_DRIVE]);
	modelListener->setReportMode(HMI1.hbar.d.mode[HBAR_M_REPORT], HMI1.hbar.d.report);

	modelListener->setSpeed(VCU.d.mcu.speed);
	modelListener->setDiscur(VCU.d.mcu.discur);

	modelListener->setTripValue(HMI1.hbar.d.trip);

	modelListener->setSignal(VCU.d.signal);
	modelListener->setBattery(VCU.d.bms.soc);

	modelListener->setSeinLeft(HMI1.d.sein.left);
	modelListener->setSeinRight(HMI1.d.sein.right);

	modelListener->setIndicator(indicator);

	modelListener->setModeSelector(HMI1.hbar.m);
	modelListener->setModeSession(session);

	modelListener->setFps(LTDC_MEASURED_FPS);
	modelListener->setState(VCU.d.state);
	modelListener->setBmsState(VCU.d.bms.run);
	modelListener->setMcuState(VCU.d.mcu.run);
	modelListener->setRegisteringState(HMI1.d.state.registering);
}

uint8_t Model::readCurrentIndicator()
{
	return indicator;
}

uint8_t Model::readIndicatorState(uint8_t index)
{
	return indicators[index];
}

void Model::reloadIndicators()
{
	uint8_t errors = 0;

	indicators[INDICATOR_ABS] = HMI1.d.state.abs;
	indicators[INDICATOR_MIRRORING] = HMI1.d.state.mirroring;
	indicators[INDICATOR_LAMP] = HMI1.d.state.lamp;
	indicators[INDICATOR_WARNING] = HMI1.d.state.warning;
	indicators[INDICATOR_OVERHEAT] = HMI1.d.state.overheat;
	indicators[INDICATOR_FINGER] = HMI1.d.state.unfinger;
	indicators[INDICATOR_UNREMOTE] = HMI1.d.state.unremote;
	indicators[INDICATOR_LOWBAT] = VCU.d.bms.soc < BMS_LOWBAT_PERCENT;

	for (uint8_t i = INDICATOR_ABS; i <= INDICATOR_LOWBAT; i++)
		errors |= indicators[i];

	indicators[INDICATOR_GO] = !HMI1.hbar.reverse && !errors && VCU.d.mcu.run;
	indicators[INDICATOR_REVERSE] = HMI1.hbar.reverse;
}

void Model::swipeIndicator()
{
	uint8_t i, found = 0;

	reloadIndicators();

	// current -> up
	for (i = indicator + 1; i <= INDICATOR_MAX; i++) {
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
	// fall-back
	if (!found)
		indicator = INDICATOR_NONE;
}

#ifdef SIMULATOR
void Model::setDefaultData()
{
	HMI1.hbar.listening = 0;
	HMI1.hbar.m = HBAR_M_DRIVE;
	HMI1.hbar.d.mode[HBAR_M_TRIP] = HBAR_M_TRIP_ODO;
	HMI1.hbar.d.mode[HBAR_M_DRIVE] = HBAR_M_DRIVE_STANDARD;
	HMI1.hbar.d.mode[HBAR_M_REPORT] = HBAR_M_REPORT_RANGE;
}

void Model::generateRandomIndicators()
{
	HMI1.d.state.abs = rand() & 1;
	HMI1.d.state.mirroring = rand() & 1;
	HMI1.d.state.lamp = rand() & 1;
	HMI1.d.state.warning = rand() & 1;
	HMI1.d.state.overheat = rand() & 1;
	HMI1.d.state.unfinger = rand() & 1;
	HMI1.d.state.unremote = rand() & 1;
	HMI1.d.state.daylight = rand() & 1;
	HMI1.hbar.reverse = rand() & 1;
}

void Model::generateRandomData()
{
	HMI1.hbar.listening = 1;

	if (ticker % 1 == 0) {
		if (VCU.d.mcu.speed >= MCU_SPEED_MAX_KPH) VCU.d.mcu.speed = 0;
		else VCU.d.mcu.speed += 5;

		if (VCU.d.mcu.discur >= MCU_DISCUR_MAX) VCU.d.mcu.discur = 0;
		else VCU.d.mcu.discur += 1;
	}

	if (ticker % 10 == 0)
		HMI1.hbar.d.trip++;

	if (ticker % 20 == 0) {
		if (HMI1.hbar.d.report >= 255) HMI1.hbar.d.report = 0;
		else HMI1.hbar.d.report++;
	}

	if(ticker % 30 == 0) {
		if (VCU.d.signal >= 100) VCU.d.signal = 0;
		else VCU.d.signal++;
	}

	if (ticker % 50 == 0) {
		if (VCU.d.bms.soc >= 100) VCU.d.bms.soc = 0;
		else VCU.d.bms.soc++;
	}

	if (ticker % 60 == 0) {
		uint8_t max = 0, *mode = NULL;

		HMI1.d.sein.left = !HMI1.d.sein.left;
		HMI1.d.sein.right = !HMI1.d.sein.right;

		switch (HMI1.hbar.m) {
		case HBAR_M_TRIP :
			mode = &HMI1.hbar.d.mode[HBAR_M_TRIP];
			max = HBAR_M_TRIP_MAX - 1;
			break;
		case HBAR_M_DRIVE:
			mode = &HMI1.hbar.d.mode[HBAR_M_DRIVE];
			max = HBAR_M_DRIVE_MAX - 1;
			break;
		case HBAR_M_REPORT:
			mode = &HMI1.hbar.d.mode[HBAR_M_REPORT];
			max = HBAR_M_REPORT_MAX - 1;
			break;
		default:
			break;
		}

		if (*mode >= max) *mode = 0;
		else (*mode)++;
	}

	if (ticker % (60*2) == 0) {
		if (indicator >= INDICATOR_MAX) indicator = 0;
		else indicator++;
	}

	if (ticker % (60*3) == 0) {
		if (HMI1.hbar.m >= HBAR_M_MAX) HMI1.hbar.m = 0;
		else HMI1.hbar.m++;
	}

	if (ticker % (60 * 60) == 0)
		generateRandomIndicators();

	switch (HMI1.hbar.m) {
	case HBAR_M_TRIP :
		modelListener->setTripMode(HMI1.hbar.d.mode[HBAR_M_TRIP]);
		break;
	case HBAR_M_DRIVE:
		modelListener->setDriveMode(HMI1.hbar.d.mode[HBAR_M_DRIVE]);
		break;
	case HBAR_M_REPORT:
		modelListener->setReportMode(HMI1.hbar.d.mode[HBAR_M_REPORT]);
		break;
	default:
		break;
	}
}
#endif

