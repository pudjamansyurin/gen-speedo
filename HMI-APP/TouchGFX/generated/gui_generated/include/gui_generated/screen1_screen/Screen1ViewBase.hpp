/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN1VIEWBASE_HPP
#define SCREEN1VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class Screen1ViewBase : public touchgfx::View<Screen1Presenter>
{
public:
    Screen1ViewBase();
    virtual ~Screen1ViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Image background;
    touchgfx::Image frontend;
    touchgfx::Image seinRight;
    touchgfx::Image seinLeft;
    touchgfx::Image engineRotation;
    touchgfx::Image speedLevel;
    touchgfx::Container container1;
    touchgfx::Image mainGo;
    touchgfx::Image mainReverse;
    touchgfx::Image batteryDrainOut;
    touchgfx::Image brakeSystemAlert;
    touchgfx::Image coolantTemperatureWarning;
    touchgfx::Image electronicErrorMessage;
    touchgfx::Image fingerscanLoginStatus;
    touchgfx::Image highBeamActivated;
    touchgfx::Image keylessIgnitionKeyDetection;
    touchgfx::Image smartphoneMirroringStatus;
    touchgfx::TextAreaWithOneWildcard textArea1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA1_SIZE = 7;
    touchgfx::Unicode::UnicodeChar textArea1Buffer[TEXTAREA1_SIZE];

private:

};

#endif // SCREEN1VIEWBASE_HPP
