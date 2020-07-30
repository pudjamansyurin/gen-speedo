/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN1VIEWBASE_HPP
#define SCREEN1VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/TiledImage.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

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
    touchgfx::TiledImage background;
    touchgfx::Image seinLeft;
    touchgfx::Image keylessKey;
    touchgfx::Image mirrorPhone;
    touchgfx::Image fingerScan;
    touchgfx::Image tripLabel;
    touchgfx::TextAreaWithOneWildcard odometerValue;
    touchgfx::TextAreaWithOneWildcard tripValue;
    touchgfx::MoveAnimator< touchgfx::ScalableImage > speedoMeter;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TRIPVALUE_SIZE = 7;
    touchgfx::Unicode::UnicodeChar tripValueBuffer[TRIPVALUE_SIZE];

private:

};

#endif // SCREEN1VIEWBASE_HPP
