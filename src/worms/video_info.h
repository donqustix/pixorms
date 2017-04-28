#ifndef VIDEOINFO_H
#define VIDEOINFO_H

#include <SDL2/SDL_pixels.h>

namespace worms
{
    struct VideoInfo
    {
        Uint32      format;
        Uint32      rMask;
        Uint32      gMask;
        Uint32      bMask;
        Uint32      aMask;
        int         bitsPerPixel;

        static VideoInfo create(const SDL_PixelFormat* pixelFormat) noexcept;
    };
}

#endif
