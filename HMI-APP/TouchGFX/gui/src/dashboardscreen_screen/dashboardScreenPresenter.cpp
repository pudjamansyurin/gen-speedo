#include <gui/dashboardscreen_screen/dashboardScreenView.hpp>
#include <gui/dashboardscreen_screen/dashboardScreenPresenter.hpp>

dashboardScreenPresenter::dashboardScreenPresenter(dashboardScreenView& v)
    : view(v)
{

}

void dashboardScreenPresenter::activate()
{

}

void dashboardScreenPresenter::deactivate()
{

}

void dashboardScreenPresenter::indicatorChanged(uint8_t index) 
{
	view.setIndicator(index);
}
void dashboardScreenPresenter::seinChanged(uint8_t leftSide, uint8_t state)
{
	view.setSein(leftSide, state);
}
void dashboardScreenPresenter::speedChanged(uint8_t value) 
{
	view.setSpeed(value * 100 / MCU_SPEED_MAX);
}
void dashboardScreenPresenter::engineRotationChanged(uint32_t value)
{
	view.setEngineRotation(value * 100 / MCU_RPM_MAX);
}
void dashboardScreenPresenter::batteryChanged(uint8_t percent)
{
	view.setBattery(percent);
}
void dashboardScreenPresenter::signalChanged(uint8_t percent)
{
	view.setSignal(percent);
}
void dashboardScreenPresenter::driveModeChanged(uint8_t index)
{
	view.setDriveMode(index);
}
void dashboardScreenPresenter::tripModeChanged(uint8_t index)
{
	view.setTripMode(index);
}
void dashboardScreenPresenter::tripValueChanged(uint32_t value)
{
	view.setTripValue(value);
}
void dashboardScreenPresenter::reportModeChanged(uint8_t index)
{
	view.setReportMode(index);
}
void dashboardScreenPresenter::reportValueChanged(uint16_t value)
{
	view.setReportValue(value);
}