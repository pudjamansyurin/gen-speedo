#ifndef WELCOMESCREENPRESENTER_HPP
#define WELCOMESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class welcomeScreenView;

class welcomeScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    welcomeScreenPresenter(welcomeScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~welcomeScreenPresenter() {};

private:
    welcomeScreenPresenter();

    welcomeScreenView& view;
};

#endif // WELCOMESCREENPRESENTER_HPP
