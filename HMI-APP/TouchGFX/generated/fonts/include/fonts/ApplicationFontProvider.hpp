/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#ifndef APPLICATIONFONTPROVIDER_HPP
#define APPLICATIONFONTPROVIDER_HPP

#include <touchgfx/FontManager.hpp>

struct Typography
{
    static const touchgfx::FontId SMALL = 0;
    static const touchgfx::FontId MEDIUM = 1;
    static const touchgfx::FontId LARGE = 2;
};

struct TypographyFontIndex
{
    static const touchgfx::FontId SMALL = 0;  // venus_rising_rg_12_4bpp
    static const touchgfx::FontId MEDIUM = 1; // venus_rising_rg_15_4bpp
    static const touchgfx::FontId LARGE = 2;  // venus_rising_rg_17_4bpp
    static const uint16_t NUMBER_OF_FONTS = 3;
};

class ApplicationFontProvider : public touchgfx::FontProvider
{
public:
    virtual touchgfx::Font* getFont(touchgfx::FontId typography);
};

#endif // APPLICATIONFONTPROVIDER_HPP
