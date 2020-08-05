/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include "BitmapDatabase.hpp"

Screen1ViewBase::Screen1ViewBase()
{

    container1.setPosition(0, 0, 800, 480);

    background.setPosition(0, 0, 800, 480);
    background.setColor(touchgfx::Color::getColorFrom24BitRGB(0, 0, 0));
    container1.add(background);

    tripUnit.setXY(292, 114);
    tripUnit.setColor(touchgfx::Color::getColorFrom24BitRGB(128, 128, 128));
    tripUnit.setLinespacing(0);
    tripUnit.setTypedText(touchgfx::TypedText(T_SINGLEUSEID1));
    container1.add(tripUnit);

    signalPercent.setXY(484, 59);
    signalPercent.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    signalPercent.setLinespacing(0);
    signalPercent.setTypedText(touchgfx::TypedText(T_SINGLEUSEID9));
    container1.add(signalPercent);

    batteryPercent.setXY(376, 59);
    batteryPercent.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    batteryPercent.setLinespacing(0);
    batteryPercent.setTypedText(touchgfx::TypedText(T_SINGLEUSEID10));
    container1.add(batteryPercent);

    signalIcon.setXY(412, 62);
    signalIcon.setBitmap(touchgfx::Bitmap(BITMAP_SIGNALICON_ID));
    container1.add(signalIcon);

    batteryIcon.setXY(302, 63);
    batteryIcon.setBitmap(touchgfx::Bitmap(BITMAP_BATTERYICON_ID));
    container1.add(batteryIcon);

    backgroundRight.setXY(556, 54);
    backgroundRight.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUNDRIGHT_ID));
    container1.add(backgroundRight);

    backgroundLeft.setXY(0, 54);
    backgroundLeft.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUNDLEFT_ID));
    container1.add(backgroundLeft);

    tripContainer.setXY(364, 98);
    tripContainer.setBitmap(touchgfx::Bitmap(BITMAP_TRIPCONTAINER_ID));
    container1.add(tripContainer);

    modeContainer.setXY(277, 364);
    modeContainer.setBitmap(touchgfx::Bitmap(BITMAP_MODECONTAINER_ID));
    container1.add(modeContainer);

    reportValue.setPosition(380, 406, 122, 20);
    reportValue.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    reportValue.setLinespacing(0);
    Unicode::snprintf(reportValueBuffer, REPORTVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID17).getText());
    reportValue.setWildcard(reportValueBuffer);
    reportValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID8));

    reportMode.setPosition(297, 406, 81, 20);
    reportMode.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    reportMode.setLinespacing(0);
    Unicode::snprintf(reportModeBuffer, REPORTMODE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID16).getText());
    reportMode.setWildcard(reportModeBuffer);
    reportMode.setTypedText(touchgfx::TypedText(T_SINGLEUSEID7));

    driveMode.setPosition(288, 368, 222, 23);
    driveMode.setColor(touchgfx::Color::getColorFrom24BitRGB(17, 170, 212));
    driveMode.setLinespacing(0);
    Unicode::snprintf(driveModeBuffer, DRIVEMODE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID15).getText());
    driveMode.setWildcard(driveModeBuffer);
    driveMode.setTypedText(touchgfx::TypedText(T_SINGLEUSEID2));

    tripValue.setPosition(374, 102, 119, 20);
    tripValue.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 255));
    tripValue.setLinespacing(0);
    Unicode::snprintf(tripValueBuffer, TRIPVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID11).getText());
    tripValue.setWildcard(tripValueBuffer);
    tripValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID3));

    tripLabel.setPosition(269, 93, 79, 20);
    tripLabel.setColor(touchgfx::Color::getColorFrom24BitRGB(128, 128, 128));
    tripLabel.setLinespacing(0);
    Unicode::snprintf(tripLabelBuffer, TRIPLABEL_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID14).getText());
    tripLabel.setWildcard(tripLabelBuffer);
    tripLabel.setTypedText(touchgfx::TypedText(T_SINGLEUSEID6));

    signalValue.setPosition(445, 59, 39, 20);
    signalValue.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    signalValue.setLinespacing(0);
    Unicode::snprintf(signalValueBuffer, SIGNALVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID13).getText());
    signalValue.setWildcard(signalValueBuffer);
    signalValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID4));

    batteryValue.setPosition(337, 59, 39, 20);
    batteryValue.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    batteryValue.setLinespacing(0);
    Unicode::snprintf(batteryValueBuffer, BATTERYVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID12).getText());
    batteryValue.setWildcard(batteryValueBuffer);
    batteryValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID5));

    add(container1);
    add(reportValue);
    add(reportMode);
    add(driveMode);
    add(tripValue);
    add(tripLabel);
    add(signalValue);
    add(batteryValue);
}

void Screen1ViewBase::setupScreen()
{

}
