#include <gui/containers/reportWheelContainer.hpp>

report_t M_REPORT;

reportWheelContainer::reportWheelContainer()
{
	Unicode::strncpy(M_REPORT.mode[0], "RANGE", REPORTMODE_SIZE);
	Unicode::strncpy(M_REPORT.mode[1], "AVG", REPORTMODE_SIZE);
	Unicode::strncpy(M_REPORT.unit[0], "KM", REPORTVALUE_SIZE);
	Unicode::strncpy(M_REPORT.unit[1], "KM/KWH", REPORTVALUE_SIZE);
}

void reportWheelContainer::initialize()
{
    reportWheelContainerBase::initialize();
}

// void reportWheelContainer::handleTickEvent()
// {
	// Unicode::snprintf(reportValueBuffer, REPORTVALUE_SIZE, "%03d", HMI1.d.mode.report);
	// reportValue.invalidate();
// }

void reportWheelContainer::updateText(uint8_t index)
{
	Unicode::snprintf(reportModeBuffer, REPORTMODE_SIZE, "%s", M_REPORT.mode[index]);
	Unicode::snprintf(reportUnitBuffer, REPORTUNIT_SIZE, "%s", M_REPORT.unit[index]);
	reportValue.setX(index ? 77 : 138);
	
	reportMode.invalidate();
	reportUnit.invalidate();
	reportValue.invalidate();
}