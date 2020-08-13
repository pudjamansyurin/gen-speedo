#ifndef INDICATORWHEELCONTAINER_HPP
#define INDICATORWHEELCONTAINER_HPP

#include <gui_generated/containers/indicatorWheelContainerBase.hpp>

class indicatorWheelContainer : public indicatorWheelContainerBase
{
public:
    indicatorWheelContainer();
    virtual ~indicatorWheelContainer() {}

    virtual void initialize();
    void updateImage(uint8_t index, uint8_t selectedIndex);
protected:
	uint16_t indicatorIcons[INDICATOR_MAX + 1];
};

#endif // INDICATORWHEELCONTAINER_HPP
