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

void dashboardScreenPresenter::setSein(uint8_t leftSide, uint8_t state)
{
	view.writeSein(leftSide, state);
}
void dashboardScreenPresenter::setSpeed(uint8_t value) 
{
	view.writeSpeed(value * 100 / MCU_SPEED_MAX);
}
void dashboardScreenPresenter::setEngineRotation(uint32_t value)
{
	view.writeEngineRotation(value * 100 / MCU_RPM_MAX);
}
void dashboardScreenPresenter::setBattery(uint8_t percent)
{
	view.writeBattery(percent);
}
void dashboardScreenPresenter::setSignal(uint8_t percent)
{
	view.writeSignal(percent);
}
void dashboardScreenPresenter::setIndicator(uint8_t index) 
{
	view.writeIndicator(index);
}
void dashboardScreenPresenter::setDriveMode(uint8_t index)
{
	view.writeDriveMode(index);
}
void dashboardScreenPresenter::setTripMode(uint8_t index)
{
	view.writeTripMode(index);
}
void dashboardScreenPresenter::setTripValue(uint32_t value)
{
	view.writeTripValue(value);
}
void dashboardScreenPresenter::setReportMode(uint8_t index)
{
	view.writeReportMode(index);
}
void dashboardScreenPresenter::setReportValue(uint16_t value)
{
	view.writeReportValue(value);
}
uint8_t dashboardScreenPresenter::getIndicatorState(uint8_t index) 
{
	return model->readIndicatorState(index);
}