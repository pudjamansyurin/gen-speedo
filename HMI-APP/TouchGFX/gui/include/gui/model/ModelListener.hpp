#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}
	
    void bind(Model* m)
    {
        model = m;
    }
	
    virtual void indicatorChanged(uint8_t index) {};
	virtual void seinChanged(uint8_t leftSide, uint8_t state) {};
	virtual void speedChanged(uint8_t value) {};
	virtual void engineRotationChanged(uint32_t value) {};
	virtual void batteryChanged(uint8_t percent) {};
	virtual void signalChanged(uint8_t percent) {};
	virtual void driveModeChanged(uint8_t index) {};
	virtual void tripModeChanged(uint8_t index) {};
	virtual void tripValueChanged(uint32_t value) {};
	virtual void reportModeChanged(uint8_t index) {};
	virtual void reportValueChanged(uint16_t value) {};
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
