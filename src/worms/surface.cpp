#include "surface.h"
#include "video_info.h"

#include <SDL2/SDL_image.h>

#include <stdexcept>

using worms::Surface;

Surface Surface::load(const std::string& filepath)
{
    SDL_Surface* const handle = ::IMG_Load(filepath.c_str());
    if (!handle)
        throw std::runtime_error{::IMG_GetError()};
    return Surface{handle};
}

Surface Surface::create(const VideoInfo& videoInfo, int width, int height)
{
    SDL_Surface* const handle =
        ::SDL_CreateRGBSurface(0, width, height, videoInfo.bitsPerPixel,
                                                 videoInfo.rMask,
                                                 videoInfo.gMask,
                                                 videoInfo.bMask,
                                                 videoInfo.aMask);
    if (!handle)
        throw std::runtime_error{::SDL_GetError()};
    return Surface{handle};
}

Surface Surface::convert(const SDL_Surface* sdlSurface, Uint32 format)
{
    SDL_Surface* const handle = ::SDL_ConvertSurfaceFormat(const_cast<SDL_Surface*>(sdlSurface), format, 0);
    if (!handle)
        throw std::runtime_error{::SDL_GetError()};
    return Surface{handle};
}

Surface::Surface(Surface&& surface) noexcept : handle{surface.handle}
{
    surface.handle = nullptr;
}

Surface::~Surface()
{
    ::SDL_FreeSurface(handle);
}

Surface& Surface::operator=(Surface&& surface) noexcept
{
    if (this == &surface) return *this;
    handle = surface.handle;
    surface.handle = nullptr;
    return *this;
}

