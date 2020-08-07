#ifndef IMAGECONTAINER_HPP
#define IMAGECONTAINER_HPP

#include <gui_generated/containers/imageContainerBase.hpp>

class imageContainer : public imageContainerBase
{
public:
    imageContainer();
    virtual ~imageContainer() {}

    virtual void initialize();
    void updateImage(Bitmap icon);
protected:
};

#endif // IMAGECONTAINER_HPP
