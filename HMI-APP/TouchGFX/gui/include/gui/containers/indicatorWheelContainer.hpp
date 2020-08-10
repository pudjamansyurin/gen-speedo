#ifndef INDICATORWHEELCONTAINER_HPP
#define INDICATORWHEELCONTAINER_HPP

#include <gui_generated/containers/indicatorWheelContainerBase.hpp>

class indicatorWheelContainer : public indicatorWheelContainerBase
{
public:
    indicatorWheelContainer();
    virtual ~indicatorWheelContainer() {}

    virtual void initialize();
    void updateImage(uint8_t index);
protected:
	uint16_t indicatorList[INDICATOR_MAX];
};

#endif // INDICATORWHEELCONTAINER_HPP
