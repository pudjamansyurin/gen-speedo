/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef DASHBOARDSCREENVIEWBASE_HPP
#define DASHBOARDSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/dashboardscreen_screen/dashboardScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/CacheableContainer.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/progress_indicators/ImageProgress.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

class dashboardScreenViewBase : public touchgfx::View<dashboardScreenPresenter>
{
public:
    dashboardScreenViewBase();
    virtual ~dashboardScreenViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box background;
    touchgfx::Image batteryLow;
    touchgfx::Image brakeAlert;
    touchgfx::Image temperatureWarning;
    touchgfx::Image errorMessage;
    touchgfx::Image fingerScan;
    touchgfx::Image keylessKey;
    touchgfx::Image beamActivated;
    touchgfx::Image none;
    touchgfx::Image mainGo;
    touchgfx::Image mainReverse;
    touchgfx::Image phoneMirroring;
    touchgfx::CacheableContainer iconContainer;
    touchgfx::MoveAnimator< touchgfx::Container > prevIconContainer;
    touchgfx::Image prevIconImage;
    touchgfx::MoveAnimator< touchgfx::Container > nextIconContainer;
    touchgfx::Image nextIconImage;
    touchgfx::Container frameContainer;
    touchgfx::TextArea tripUnit;
    touchgfx::TextArea signalPercent;
    touchgfx::TextArea batteryPercent;
    touchgfx::Image signalIcon;
    touchgfx::Image batteryIcon;
    touchgfx::Image backgroundRight;
    touchgfx::Image backgroundLeft;
    touchgfx::Image tripBox;
    touchgfx::Image driveBox;
    touchgfx::Image scanningIcon;
    touchgfx::CacheableContainer seinLeftContainer;
    touchgfx::Image seinLeft;
    touchgfx::Container seinRightContainer;
    touchgfx::Image seinRight;
    touchgfx::CacheableContainer reportModeContainer;
    touchgfx::MoveAnimator< touchgfx::Container > prevReportModeContainer;
    touchgfx::TextArea prevReportUnitText;
    touchgfx::TextArea prevReportModeText;
    touchgfx::TextAreaWithOneWildcard prevReportValueText;
    touchgfx::MoveAnimator< touchgfx::Container > nextReportModeContainer;
    touchgfx::TextArea nextReportUnitText;
    touchgfx::TextArea nextReportModeText;
    touchgfx::TextAreaWithOneWildcard nextReportValueText;
    touchgfx::CacheableContainer driveModeContainer;
    touchgfx::MoveAnimator< touchgfx::TextAreaWithOneWildcard > prevDriveModeText;
    touchgfx::MoveAnimator< touchgfx::TextAreaWithOneWildcard > nextDriveModeText;
    touchgfx::CacheableContainer tripModeContainer;
    touchgfx::MoveAnimator< touchgfx::TextAreaWithOneWildcard > prevTripModeText;
    touchgfx::MoveAnimator< touchgfx::TextAreaWithOneWildcard > nextTripModeText;
    touchgfx::TextAreaWithOneWildcard tripValue;
    touchgfx::TextAreaWithOneWildcard signalValue;
    touchgfx::TextAreaWithOneWildcard batteryValue;
    touchgfx::ImageProgress discurProgress;
    touchgfx::ImageProgress speedProgress;
    touchgfx::TextAreaWithOneWildcard stateValue;
    touchgfx::TextAreaWithOneWildcard bmsValue;
    touchgfx::TextAreaWithOneWildcard mcuValue;
    touchgfx::TextArea canState;

    /*
     * Wildcard Buffers
     */
    static const uint16_t PREVREPORTVALUETEXT_SIZE = 11;
    touchgfx::Unicode::UnicodeChar prevReportValueTextBuffer[PREVREPORTVALUETEXT_SIZE];
    static const uint16_t NEXTREPORTVALUETEXT_SIZE = 11;
    touchgfx::Unicode::UnicodeChar nextReportValueTextBuffer[NEXTREPORTVALUETEXT_SIZE];
    static const uint16_t PREVDRIVEMODETEXT_SIZE = 12;
    touchgfx::Unicode::UnicodeChar prevDriveModeTextBuffer[PREVDRIVEMODETEXT_SIZE];
    static const uint16_t NEXTDRIVEMODETEXT_SIZE = 12;
    touchgfx::Unicode::UnicodeChar nextDriveModeTextBuffer[NEXTDRIVEMODETEXT_SIZE];
    static const uint16_t PREVTRIPMODETEXT_SIZE = 7;
    touchgfx::Unicode::UnicodeChar prevTripModeTextBuffer[PREVTRIPMODETEXT_SIZE];
    static const uint16_t NEXTTRIPMODETEXT_SIZE = 7;
    touchgfx::Unicode::UnicodeChar nextTripModeTextBuffer[NEXTTRIPMODETEXT_SIZE];
    static const uint16_t TRIPVALUE_SIZE = 7;
    touchgfx::Unicode::UnicodeChar tripValueBuffer[TRIPVALUE_SIZE];
    static const uint16_t SIGNALVALUE_SIZE = 4;
    touchgfx::Unicode::UnicodeChar signalValueBuffer[SIGNALVALUE_SIZE];
    static const uint16_t BATTERYVALUE_SIZE = 4;
    touchgfx::Unicode::UnicodeChar batteryValueBuffer[BATTERYVALUE_SIZE];
    static const uint16_t STATEVALUE_SIZE = 2;
    touchgfx::Unicode::UnicodeChar stateValueBuffer[STATEVALUE_SIZE];
    static const uint16_t BMSVALUE_SIZE = 2;
    touchgfx::Unicode::UnicodeChar bmsValueBuffer[BMSVALUE_SIZE];
    static const uint16_t MCUVALUE_SIZE = 2;
    touchgfx::Unicode::UnicodeChar mcuValueBuffer[MCUVALUE_SIZE];

private:

};

#endif // DASHBOARDSCREENVIEWBASE_HPP
