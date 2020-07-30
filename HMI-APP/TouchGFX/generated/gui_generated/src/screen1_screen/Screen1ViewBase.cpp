/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

Screen1ViewBase::Screen1ViewBase()
{

    background.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_ID));
    background.setPosition(0, 0, 320, 240);
    background.setOffset(0, 0);

    seinLeft.setXY(275, 83);
    seinLeft.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_SEIN_ID));

    keylessKey.setXY(228, 133);
    keylessKey.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_KEYLESS_ID));

    mirrorPhone.setXY(261, 129);
    mirrorPhone.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_MIRROR_ID));

    fingerScan.setXY(293, 127);
    fingerScan.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_FINGER_ID));

    tripLabel.setXY(127, 89);
    tripLabel.setBitmap(touchgfx::Bitmap(BITMAP_HMI_LEFT_TRIP_B_ID));

    odometerValue.setPosition(159, 106, 64, 25);
    odometerValue.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    odometerValue.setLinespacing(0);
    odometerValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID2));

    tripValue.setPosition(159, 82, 64, 25);
    tripValue.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    tripValue.setLinespacing(0);
    tripValueBuffer[0] = 0;
    tripValue.setWildcard(tripValueBuffer);
    tripValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID1));

    speedoMeter.setBitmap(touchgfx::Bitmap(BITMAP_CLOCK_STANDARD_SECOND_HAND_ID));
    speedoMeter.setPosition(176, 67, 9, 127);
    speedoMeter.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    add(background);
    add(seinLeft);
    add(keylessKey);
    add(mirrorPhone);
    add(fingerScan);
    add(tripLabel);
    add(odometerValue);
    add(tripValue);
    add(speedoMeter);
}

void Screen1ViewBase::setupScreen()
{

}
