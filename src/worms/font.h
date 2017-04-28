#ifndef FONT_H
#define FONT_H

#include "resource.h"

#include <SDL2/SDL_ttf.h>

#include <string>

namespace worms
{
    class Font : public Resource
    {
        TTF_Font* handle;

    public:
        static Font load(const std::string& filepath, int ptsize);

        explicit Font(TTF_Font* ttfFont) noexcept : handle{ttfFont} {}
        Font(Font&& font) noexcept;
        ~Font();

        Font& operator=(Font&& font) noexcept;

        const auto* getHandle() const noexcept {return handle;}
    };
}

#endif
