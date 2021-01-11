/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef DASHBOARDSCREENVIEWBASE_HPP
#define DASHBOARDSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/dashboardscreen_screen/dashboardScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/progress_indicators/ImageProgress.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
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
    touchgfx::Container indicatorImages;
    touchgfx::Image batteryLow;
    touchgfx::Image brakeAlert;
    touchgfx::Image temperatureWarning;
    touchgfx::Image errorMessage;
    touchgfx::Image fingerScan;
    touchgfx::Image beamActivated;
    touchgfx::Image keylessKey;
    touchgfx::Image phoneMirroring;
    touchgfx::Image mainGo;
    touchgfx::Image mainReverse;
    touchgfx::Container iconContainer;
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
    touchgfx::Container seinLeftContainer;
    touchgfx::MoveAnimator< touchgfx::Image > seinLeft;
    touchgfx::Container seinRightContainer;
    touchgfx::MoveAnimator< touchgfx::Image > seinRight;
    touchgfx::ImageProgress engineProgress;
    touchgfx::ImageProgress speedProgress;
    touchgfx::Container reportModeContainer;
    touchgfx::MoveAnimator< touchgfx::Container > prevReportModeContainer;
    touchgfx::TextArea prevReportUnitText;
    touchgfx::TextArea prevReportModeText;
    touchgfx::TextAreaWithOneWildcard prevReportValueText;
    touchgfx::MoveAnimator< touchgfx::Container > nextReportModeContainer;
    touchgfx::TextArea nextReportUnitText;
    touchgfx::TextArea nextReportModeText;
    touchgfx::TextAreaWithOneWildcard nextReportValueText;
    touchgfx::Container driveModeContainer;
    touchgfx::MoveAnimator< touchgfx::TextAreaWithOneWildcard > prevDriveModeText;
    touchgfx::MoveAnimator< touchgfx::TextAreaWithOneWildcard > nextDriveModeText;
    touchgfx::TextAreaWithOneWildcard tripValue;
    touchgfx::Container tripModeContainer;
    touchgfx::MoveAnimator< touchgfx::TextAreaWithOneWildcard > prevTripModeText;
    touchgfx::MoveAnimator< touchgfx::TextAreaWithOneWildcard > nextTripModeText;
    touchgfx::TextAreaWithOneWildcard signalValue;
    touchgfx::TextAreaWithOneWildcard batteryValue;

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
    static const uint16_t TRIPVALUE_SIZE = 7;
    touchgfx::Unicode::UnicodeChar tripValueBuffer[TRIPVALUE_SIZE];
    static const uint16_t PREVTRIPMODETEXT_SIZE = 7;
    touchgfx::Unicode::UnicodeChar prevTripModeTextBuffer[PREVTRIPMODETEXT_SIZE];
    static const uint16_t NEXTTRIPMODETEXT_SIZE = 7;
    touchgfx::Unicode::UnicodeChar nextTripModeTextBuffer[NEXTTRIPMODETEXT_SIZE];
    static const uint16_t SIGNALVALUE_SIZE = 4;
    touchgfx::Unicode::UnicodeChar signalValueBuffer[SIGNALVALUE_SIZE];
    static const uint16_t BATTERYVALUE_SIZE = 4;
    touchgfx::Unicode::UnicodeChar batteryValueBuffer[BATTERYVALUE_SIZE];

private:

};

#endif // DASHBOARDSCREENVIEWBASE_HPP
