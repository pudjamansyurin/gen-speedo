/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

Screen1ViewBase::Screen1ViewBase()
{

    tiledImage1.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_ID));
    tiledImage1.setPosition(0, 0, 320, 240);
    tiledImage1.setOffset(0, 0);

    image1.setXY(275, 84);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_SEIN_ID));

    image2.setXY(228, 133);
    image2.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_KEYLESS_ID));

    image3.setXY(261, 129);
    image3.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_MIRROR_ID));

    image4.setXY(293, 127);
    image4.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_FINGER_ID));

    image5.setXY(127, 89);
    image5.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_TRIP_B_ID));

    textArea1.setXY(159, 106);
    textArea1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID2));

    textArea2.setXY(159, 83);
    textArea2.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T_SINGLEUSEID3));

    scalableImage1.setBitmap(touchgfx::Bitmap(BITMAP_CLOCK_STANDARD_SECOND_HAND_ID));
    scalableImage1.setPosition(176, 67, 9, 127);
    scalableImage1.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    add(tiledImage1);
    add(image1);
    add(image2);
    add(image3);
    add(image4);
    add(image5);
    add(textArea1);
    add(textArea2);
    add(scalableImage1);
}

void Screen1ViewBase::setupScreen()
{

}
