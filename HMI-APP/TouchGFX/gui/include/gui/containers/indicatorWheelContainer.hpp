#ifndef INDICATORWHEELCONTAINER_HPP
#define INDICATORWHEELCONTAINER_HPP

#include <gui_generated/containers/indicatorWheelContainerBase.hpp>

class indicatorWheelContainer : public indicatorWheelContainerBase
{
public:
    indicatorWheelContainer();
    virtual ~indicatorWheelContainer() {}

    virtual void initialize();
    void updateImage(Bitmap icon);
protected:
};

#endif // INDICATORWHEELCONTAINER_HPP
