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
#include <touchgfx/containers/scrollers/ScrollWheel.hpp>
#include <gui/containers/indicatorWheelContainer.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/progress_indicators/ImageProgress.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/containers/reportWheelContainer.hpp>
#include <gui/containers/driveWheelContainer.hpp>
#include <gui/containers/tripWheelContainer.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

class dashboardScreenViewBase : public touchgfx::View<dashboardScreenPresenter>
{
public:
    dashboardScreenViewBase();
    virtual ~dashboardScreenViewBase() {}
    virtual void setupScreen();

    virtual void indicatorWheelUpdateItem(indicatorWheelContainer& item, int16_t itemIndex)
    {
        // Override and implement this function in dashboardScreen
    }

    virtual void reportWheelUpdateItem(reportWheelContainer& item, int16_t itemIndex)
    {
        // Override and implement this function in dashboardScreen
    }

    virtual void driveWheelUpdateItem(driveWheelContainer& item, int16_t itemIndex)
    {
        // Override and implement this function in dashboardScreen
    }

    virtual void tripWheelUpdateItem(tripWheelContainer& item, int16_t itemIndex)
    {
        // Override and implement this function in dashboardScreen
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
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
    touchgfx::Container indicatorContainer;
    touchgfx::MoveAnimator< touchgfx::Image > indicatorImage;
    touchgfx::ScrollWheel indicatorWheel;
    touchgfx::DrawableListItems<indicatorWheelContainer, 3> indicatorWheelListItems;
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
    touchgfx::TextAreaWithOneWildcard reportValue;
    touchgfx::ScrollWheel reportWheel;
    touchgfx::DrawableListItems<reportWheelContainer, 2> reportWheelListItems;
    touchgfx::ScrollWheel driveWheel;
    touchgfx::DrawableListItems<driveWheelContainer, 2> driveWheelListItems;
    touchgfx::TextAreaWithOneWildcard tripValue;
    touchgfx::ScrollWheel tripWheel;
    touchgfx::DrawableListItems<tripWheelContainer, 2> tripWheelListItems;
    touchgfx::TextAreaWithOneWildcard signalValue;
    touchgfx::TextAreaWithOneWildcard batteryValue;

    /*
     * Wildcard Buffers
     */
    static const uint16_t REPORTVALUE_SIZE = 11;
    touchgfx::Unicode::UnicodeChar reportValueBuffer[REPORTVALUE_SIZE];
    static const uint16_t TRIPVALUE_SIZE = 7;
    touchgfx::Unicode::UnicodeChar tripValueBuffer[TRIPVALUE_SIZE];
    static const uint16_t SIGNALVALUE_SIZE = 4;
    touchgfx::Unicode::UnicodeChar signalValueBuffer[SIGNALVALUE_SIZE];
    static const uint16_t BATTERYVALUE_SIZE = 4;
    touchgfx::Unicode::UnicodeChar batteryValueBuffer[BATTERYVALUE_SIZE];

private:
    touchgfx::Callback<dashboardScreenViewBase, touchgfx::DrawableListItemsInterface*, int16_t, int16_t> updateItemCallback;
    void updateItemCallbackHandler(touchgfx::DrawableListItemsInterface* items, int16_t containerIndex, int16_t itemIndex);

};

#endif // DASHBOARDSCREENVIEWBASE_HPP
