#ifndef STATICSCREENVIEW_HPP
#define STATICSCREENVIEW_HPP

#include <gui_generated/staticscreen_screen/staticScreenViewBase.hpp>
#include <gui/staticscreen_screen/staticScreenPresenter.hpp>

class staticScreenView : public staticScreenViewBase
{
public:
    staticScreenView();
    virtual ~staticScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
protected:
    uint16_t ticker;
    bool colored;
};

#endif // STATICSCREENVIEW_HPP
