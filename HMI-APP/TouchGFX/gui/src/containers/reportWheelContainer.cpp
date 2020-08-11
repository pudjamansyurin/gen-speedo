#include <gui/containers/reportWheelContainer.hpp>

report_t M_REPORT;

reportWheelContainer::reportWheelContainer()
{
	Unicode::strncpy(M_REPORT.mode[0], "RANGE", REPORTMODE_SIZE);
	Unicode::strncpy(M_REPORT.mode[1], "AVG", REPORTMODE_SIZE);
	Unicode::strncpy(M_REPORT.unit[0], "KM", REPORTUNIT_SIZE);
	Unicode::strncpy(M_REPORT.unit[1], "KM/KWH", REPORTUNIT_SIZE);
}

void reportWheelContainer::initialize()
{
    reportWheelContainerBase::initialize();
}

void reportWheelContainer::updateText(uint8_t index)
{
	Unicode::snprintf(reportModeBuffer, REPORTMODE_SIZE, "%s", M_REPORT.mode[index]);
	Unicode::snprintf(reportUnitBuffer, REPORTUNIT_SIZE, "%s", M_REPORT.unit[index]);
	
	reportMode.invalidate();
	reportUnit.invalidate();
}