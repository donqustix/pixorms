#include "font_bitmap.h"
#include "font.h"
#include "surface.h"

#include <SDL2/SDL_ttf.h>

#include <stdexcept>
#include <utility>

using worms::FontBitmap;

FontBitmap FontBitmap::generate(const Font& font, const SDL_Renderer* sdlRenderer)
{
    const int symbolSize = ::TTF_FontHeight(font.getHandle());

    const int w = FontBitmap::INDEX_COUNT * symbolSize;
    const int h = symbolSize;

    auto surface = Surface::create(w, h, 32, SDL_PIXELFORMAT_RGBA32);
    
    for (Uint16 i = FontBitmap::BEG; i < FontBitmap::END; ++i)
    {
        const Surface symbolSurface{
            [&font, i] {
                SDL_Surface* const handle =
                    ::TTF_RenderGlyph_Solid(const_cast<TTF_Font*>(font.getHandle()), i, {0xFF, 0xFF, 0xFF, 0xFF});
                if (!handle)
                    throw std::runtime_error{::TTF_GetError()};
                return handle;
            }()
        };

        SDL_Rect dstrect{(i - FontBitmap::BEG) * symbolSize, 0, symbolSize, symbolSize};
        
        ::SDL_BlitSurface(const_cast<SDL_Surface*>(symbolSurface.getHandle()), nullptr,
                          const_cast<SDL_Surface*>(      surface.getHandle()), &dstrect);
    }
    return {Texture::convert(sdlRenderer, surface.getHandle()), symbolSize};
}

FontBitmap::FontBitmap(Texture texture, int symbolSize) noexcept :
    texture{std::move(texture)}, symbolSize{symbolSize}
{
}

