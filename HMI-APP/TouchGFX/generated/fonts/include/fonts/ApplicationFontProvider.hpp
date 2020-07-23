/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#ifndef APPLICATIONFONTPROVIDER_HPP
#define APPLICATIONFONTPROVIDER_HPP

#include <touchgfx/FontManager.hpp>

struct Typography
{
    static const touchgfx::FontId DIGITALCLOCK = 0;
};

struct TypographyFontIndex
{
    static const touchgfx::FontId DIGITALCLOCK = 0; // Asap_Regular_24_4bpp
    static const uint16_t NUMBER_OF_FONTS = 1;
};

class ApplicationFontProvider : public touchgfx::FontProvider
{
public:
    virtual touchgfx::Font* getFont(touchgfx::FontId typography);
};

#endif // APPLICATIONFONTPROVIDER_HPP
