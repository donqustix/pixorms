#ifndef FONTBITMAP_H
#define FONTBITMAP_H

#include "resource.h"
#include "texture.h"

#include <SDL2/SDL_render.h>

namespace worms
{
    class Font;

    struct FontBitmap : public Resource
    {
        static constexpr Uint16   BEG         =        20;
        static constexpr Uint16   END         =       127;
        static constexpr Uint16   INDEX_COUNT = END - BEG;

        Texture     texture;
        int         symbolSize;

        static FontBitmap generate(const Font&                  font,
                                   const SDL_Renderer*          sdlRenderer);

        FontBitmap(Texture texture, int symbolSize) noexcept;
    };
}

#endif
