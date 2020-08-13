#include <gui/containers/indicatorWheelContainer.hpp>
#include "BitmapDatabase.hpp"

indicatorWheelContainer::indicatorWheelContainer() :
	indicatorIcons{
		BITMAP_MAINREVERSE_ID,
		BITMAP_MAINGO_ID,
        BITMAP_BRAKESYSTEMALERT_ID,
        BITMAP_SMARTPHONEMIRRORINGSTATUS_ID,
        BITMAP_HIGHBEAMACTIVATED_ID,
        BITMAP_ELECTRONICERRORMESSAGE_ID,
        BITMAP_COOLANTTEMPERATUREWARNING_ID,
        BITMAP_FINGERSCANLOGINSTATUS_ID,
        BITMAP_KEYLESSIGNITIONKEYDETECTION_ID,
		BITMAP_BATTERYDRAINOUT_ID,
	}
{

}

void indicatorWheelContainer::initialize()
{
    indicatorWheelContainerBase::initialize();
}

void indicatorWheelContainer::updateImage(uint8_t index)
{
	Bitmap icon = Bitmap(indicatorIcons[index]);

	indicatorImage.setXY(
		(getWidth() - icon.getWidth()) / 2,
		(getHeight() - icon.getHeight()) / 2
	);
	indicatorImage.setBitmap(icon);
	indicatorImage.invalidate();
}
