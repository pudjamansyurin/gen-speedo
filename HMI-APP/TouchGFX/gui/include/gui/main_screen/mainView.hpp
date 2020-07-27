#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/mainViewBase.hpp>
#include <gui/main_screen/mainPresenter.hpp>

class mainView : public mainViewBase
{
public:
    mainView();
    virtual ~mainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
protected:
    int tickCounter;
/*     int analogHours;
    int analogMinutes;
    int analogSeconds;
    int digitalHours;
    int digitalMinutes;
    int digitalSeconds; */
};

#endif // MAIN_VIEW_HPP
