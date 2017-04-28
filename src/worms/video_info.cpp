#include "video_info.h"

using worms::VideoInfo;

VideoInfo VideoInfo::create(const SDL_PixelFormat* pixelFormat) noexcept
{
    return {pixelFormat->format, pixelFormat->Rmask,
                                 pixelFormat->Gmask,
                                 pixelFormat->Bmask,
                                 pixelFormat->Amask, pixelFormat->BitsPerPixel};
}

