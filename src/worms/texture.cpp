#include "texture.h"

#include <stdexcept>

using worms::Texture;

Texture Texture::create(const SDL_Renderer*         sdlRenderer,
                        Uint32                      format,
                        int                         access,
                        int                         width,
                        int                         height)
{
    SDL_Texture* const handle =
        ::SDL_CreateTexture(const_cast<SDL_Renderer*>(sdlRenderer), format, access, width, height);
    if (!handle)
        throw std::runtime_error{::SDL_GetError()};
    return Texture{handle};
}

Texture Texture::convert(const SDL_Renderer*            sdlRenderer,
                         const SDL_Surface*             sdlSurface)
{
    SDL_Texture* const handle = ::SDL_CreateTextureFromSurface(const_cast<SDL_Renderer*>(sdlRenderer),
                                                               const_cast<SDL_Surface *>(sdlSurface));
    if (!handle)
        throw std::runtime_error{::SDL_GetError()};
    return Texture{handle};
}

Texture::Texture(Texture&& texture) noexcept : handle{texture.handle}
{
    texture.handle = nullptr;
}

Texture::~Texture()
{
    ::SDL_DestroyTexture(handle);
}

Texture& Texture::operator=(Texture&& texture) noexcept
{
    if (this == &texture) return *this;
    handle = texture.handle;
    texture.handle = nullptr;
    return *this;
}

Texture::Info Texture::requestInfo() const noexcept
{
    Uint32 format;
    int access, w, h;
    ::SDL_QueryTexture(handle, &format, &access, &w, &h);
    return {format, access, w, h};
}

