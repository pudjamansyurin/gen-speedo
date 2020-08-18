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
	static uint8_t init = 1, _value;
	
	if (init || _value != value) {
		_value = value;
		init = 0;	
		view.writeSpeed(value * 100 / MCU_SPEED_MAX);
	}
}
void dashboardScreenPresenter::setEngineRotation(uint32_t value)
{
	static uint8_t init = 1;
	static uint32_t _value;
	
	if (init || _value != value) {
		_value = value;
		init = 0;
		view.writeEngineRotation(value * 100 / MCU_RPM_MAX);
	}
}
void dashboardScreenPresenter::setBattery(uint8_t percent)
{
	static uint8_t init = 1, _percent;
	
	if (init || _percent != percent) {
		_percent = percent;
		init = 0;	
		view.writeBattery(percent);
	}
}
void dashboardScreenPresenter::setSignal(uint8_t percent)
{
	static uint8_t init = 1, _percent;
	
	if (init || _percent != percent) {
		_percent = percent;
		init = 0;
		view.writeSignal(percent);
	}
}
void dashboardScreenPresenter::setIndicator(uint8_t index) 
{
	static uint8_t init = 1, _index;
	
	if (init || _index != index) {
		_index = index;
		init = 0;
		view.writeIndicator(index);
	}
}
void dashboardScreenPresenter::setDriveMode(uint8_t index)
{
	static uint8_t init = 1, _index;
	
	if (init || _index != index) {
		_index = index;
		init = 0;
		view.writeDriveMode(index);
	}
}
void dashboardScreenPresenter::setTripMode(uint8_t index)
{
	static uint8_t init = 1, _index;
	
	if (init || _index != index) {
		_index = index;
		init = 0;
		view.writeTripMode(index);
	}
}
void dashboardScreenPresenter::setTripValue(uint32_t value)
{
	static uint8_t init = 1;
	static uint32_t _value;
	
	if (init || _value != value) {
		_value = value;
		init = 0;
		view.writeTripValue(value);
	}
}
void dashboardScreenPresenter::setReportMode(uint8_t index)
{
	static uint8_t init = 1, _index;
	
	if (init || _index != index) {
		_index = index;
		init = 0;
		view.writeReportMode(index);
	}
}
void dashboardScreenPresenter::setReportValue(uint16_t value)
{
	static uint8_t init = 1;
	static uint16_t _value;
	
	if (init || _value != value) {
		_value = value;
		init = 0;
		view.writeReportValue(value);
	}
}
void dashboardScreenPresenter::setModeSelector(uint8_t mode)
{
	static uint8_t init = 1, _mode;
	
	if (init || _mode != mode) {
		_mode = mode;
		init = 0;
		view.writeModeSelector(mode);
	}
}
void dashboardScreenPresenter::setModeVisible(uint8_t state)
{
	static uint8_t init = 1, _state;
	
	if (init || _state != state) {
		_state = state;
		init = 0;
		view.writeModeVisible(state);
	}
}

uint8_t dashboardScreenPresenter::getIndicatorState(uint8_t index) 
{
	return model->readIndicatorState(index);
}
uint8_t dashboardScreenPresenter::getCurrentIndicator() 
{
	return model->readCurrentIndicator();
}
