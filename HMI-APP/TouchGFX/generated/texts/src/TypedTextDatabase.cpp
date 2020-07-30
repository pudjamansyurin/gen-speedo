/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <touchgfx/TypedText.hpp>
#include <fonts/GeneratedFont.hpp>
#include <texts/TypedTextDatabase.hpp>

extern touchgfx::GeneratedFont& getFont_venus_rising_rg_15_4bpp();
extern touchgfx::GeneratedFont& getFont_venus_rising_rg_17_4bpp();

const touchgfx::Font* _fonts[] =
{
    &(getFont_venus_rising_rg_15_4bpp()),
    &(getFont_venus_rising_rg_17_4bpp())
};

extern const touchgfx::TypedText::TypedTextData typedText_database_DEFAULT[];
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
const touchgfx::TypedText::TypedTextData typedText_database_DEFAULT[] TEXT_LOCATION_FLASH_ATTRIBUTE =
{
    { 1, touchgfx::RIGHT, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR }
};

TEXT_LOCATION_FLASH_PRAGMA
const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[] TEXT_LOCATION_FLASH_ATTRIBUTE =
{
    typedText_database_DEFAULT
};

namespace TypedTextDatabase
{
const touchgfx::TypedText::TypedTextData* getInstance(touchgfx::LanguageId id)
{
    return typedTextDatabaseArray[id];
}

uint16_t getInstanceSize()
{
    return sizeof(typedText_database_DEFAULT) / sizeof(touchgfx::TypedText::TypedTextData);
}

const touchgfx::Font** getFonts()
{
    return _fonts;
}

const touchgfx::Font* setFont(touchgfx::FontId fontId, const touchgfx::Font* font)
{
    const touchgfx::Font* old = _fonts[fontId];
    _fonts[fontId] = font;
    return old;
}

void resetFont(touchgfx::FontId fontId)
{
    switch (fontId)
    {
    case 0:
        _fonts[0] = &(getFont_venus_rising_rg_15_4bpp());
        break;
    case 1:
        _fonts[1] = &(getFont_venus_rising_rg_17_4bpp());
        break;
    }
}
}  // namespace TypedTextDatabase
