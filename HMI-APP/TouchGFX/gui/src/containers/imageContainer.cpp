#include <gui/containers/imageContainer.hpp>
#include "BitmapDatabase.hpp"

imageContainer::imageContainer()
{

}

void imageContainer::initialize()
{
    imageContainerBase::initialize();
}

void imageContainer::updateImage(Bitmap icon)
{
    image.setXY(
		(getWidth() - icon.getWidth()) / 2, 
		(getHeight() - icon.getHeight()) / 2
	);
    image.setBitmap(icon);
    image.invalidate();
}