/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/reportWheelContainerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

reportWheelContainerBase::reportWheelContainerBase()
{
    setWidth(227);
    setHeight(18);
    reportUnit.setPosition(121, 0, 105, 18);
    reportUnit.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    reportUnit.setLinespacing(0);
    Unicode::snprintf(reportUnitBuffer, REPORTUNIT_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID27).getText());
    reportUnit.setWildcard(reportUnitBuffer);
    reportUnit.setTypedText(touchgfx::TypedText(T_SINGLEUSEID26));

    reportValue.setPosition(138, 0, 50, 18);
    reportValue.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    reportValue.setLinespacing(0);
    Unicode::snprintf(reportValueBuffer, REPORTVALUE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID25).getText());
    reportValue.setWildcard(reportValueBuffer);
    reportValue.setTypedText(touchgfx::TypedText(T_SINGLEUSEID24));

    reportMode.setXY(0, 0);
    reportMode.setColor(touchgfx::Color::getColorFrom24BitRGB(179, 179, 179));
    reportMode.setLinespacing(0);
    Unicode::snprintf(reportModeBuffer, REPORTMODE_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID23).getText());
    reportMode.setWildcard(reportModeBuffer);
    reportMode.resizeToCurrentText();
    reportMode.setTypedText(touchgfx::TypedText(T_SINGLEUSEID22));

    add(reportUnit);
    add(reportValue);
    add(reportMode);
}

void reportWheelContainerBase::initialize()
{

}
