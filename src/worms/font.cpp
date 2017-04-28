#include "font.h"

#include <stdexcept>

using worms::Font;

Font Font::load(const std::string& filepath, int ptsize)
{
    TTF_Font* const ttfFont = ::TTF_OpenFont(filepath.c_str(), ptsize);
    if (!ttfFont)
        throw std::runtime_error{"there is no the font " + filepath};
    return Font{ttfFont};
}

Font::Font(Font&& font) noexcept : handle{font.handle}
{
    font.handle = nullptr;
}

Font::~Font()
{
    ::TTF_CloseFont(handle);
}

Font& Font::operator=(Font&& font) noexcept
{
    if (this == &font) return *this;
    handle = font.handle;
    font.handle = nullptr;
    return *this;
}

