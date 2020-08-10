#include <gui/containers/indicatorWheelContainer.hpp>

indicatorWheelContainer::indicatorWheelContainer()
{

}

void indicatorWheelContainer::initialize()
{
    indicatorWheelContainerBase::initialize();
}

void indicatorWheelContainer::updateImage(Bitmap icon)
{
    indicatorImage.setXY(
		(getWidth() - icon.getWidth()) / 2, 
		(getHeight() - icon.getHeight()) / 2
	);
    indicatorImage.setBitmap(icon);
    indicatorImage.invalidate();
}