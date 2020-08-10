#include <gui/containers/tripWheelContainer.hpp>

trip_t M_TRIP;

tripWheelContainer::tripWheelContainer()
{
	Unicode::strncpy(M_TRIP.mode[0], "ODO", TRIPMODE_SIZE);
	Unicode::strncpy(M_TRIP.mode[1], "TRIP A", TRIPMODE_SIZE);
	Unicode::strncpy(M_TRIP.mode[2], "TRIP B", TRIPMODE_SIZE);
}

void tripWheelContainer::initialize()
{
    tripWheelContainerBase::initialize();
}

void tripWheelContainer::updateText(uint8_t index)
{
	Unicode::snprintf(tripModeBuffer, TRIPMODE_SIZE, "%s", M_TRIP.mode[index]);
	tripMode.invalidate();
}
