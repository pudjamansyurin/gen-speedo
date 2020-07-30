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

    tripValue.setPosition(159, 83, 64, 25);
    tripValue.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    tripValue.setLinespacing(0);
    Unicode::snprintf(tripValueBuffer, TRIPVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID4).getText());
    tripValue.setWildcard(tripValueBuffer);
    tripValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID1));

    odomValue.setPosition(159, 107, 64, 25);
    odomValue.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    odomValue.setLinespacing(0);
    Unicode::snprintf(odomValueBuffer, ODOMVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID3).getText());
    odomValue.setWildcard(odomValueBuffer);
    odomValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID2));

    speedoMeter.setXY(80, 65);
    speedoMeter.setBitmap(touchgfx::Bitmap(BITMAP_CLOCK_STANDARD_SECOND_HAND_ID));
    speedoMeter.setWidth(200);
    speedoMeter.setHeight(200);
    speedoMeter.setBitmapPosition(96.300f, 33.600f);
    speedoMeter.setScale(1.400f);
    speedoMeter.setCameraDistance(1000.000f);
    speedoMeter.setOrigo(100.000f, 100.000f, 1000.000f);
    speedoMeter.setCamera(100.000f, 100.000f);
    speedoMeter.updateAngles(0.000f, 0.000f, -1.570f);
    speedoMeter.setRenderingAlgorithm(touchgfx::TextureMapper::NEAREST_NEIGHBOR);

    add(background);
    add(seinLeft);
    add(keylessKey);
    add(mirrorPhone);
    add(fingerScan);
    add(tripLabel);
    add(tripValue);
    add(odomValue);
    add(speedoMeter);
}

void Screen1ViewBase::setupScreen()
{

}
