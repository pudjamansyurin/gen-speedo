/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/imageContainerBase.hpp>
#include "BitmapDatabase.hpp"

imageContainerBase::imageContainerBase()
{
    setWidth(230);
    setHeight(230);
    image.setXY(10, 75);
    image.setBitmap(touchgfx::Bitmap(BITMAP_MAINGO_ID));

    add(image);
}

void imageContainerBase::initialize()
{

}