#include <gui/containers/driveWheelContainer.hpp>
#include <touchgfx/Color.hpp>

drive_t M_DRIVE;

driveWheelContainer::driveWheelContainer() 
{
	M_DRIVE.color[0] = touchgfx::Color::getColorFrom24BitRGB(255, 255, 0);
	M_DRIVE.color[1] = touchgfx::Color::getColorFrom24BitRGB(0, 255, 0);
	M_DRIVE.color[2] = touchgfx::Color::getColorFrom24BitRGB(255, 0, 0);
	M_DRIVE.color[3] = touchgfx::Color::getColorFrom24BitRGB(0, 255, 255);

	touchgfx::Unicode::strncpy(M_DRIVE.mode[0], "ECONOMIC", DRIVEMODE_SIZE);
	touchgfx::Unicode::strncpy(M_DRIVE.mode[1], "STANDARD", DRIVEMODE_SIZE);
	touchgfx::Unicode::strncpy(M_DRIVE.mode[2], "SPORT", DRIVEMODE_SIZE);
	touchgfx::Unicode::strncpy(M_DRIVE.mode[3], "PERFORMANCE", DRIVEMODE_SIZE);
}

void driveWheelContainer::initialize()
{
    driveWheelContainerBase::initialize();
}

void driveWheelContainer::updateText(uint8_t index)
{
	touchgfx::Unicode::snprintf(driveModeBuffer, DRIVEMODE_SIZE, "%s", M_DRIVE.mode[index]);
	driveMode.setColor(M_DRIVE.color[index]);
	driveMode.invalidate();
	touchgfx_printf("%d\n", index);
}
