#ifndef TEXTURE_H
#define TEXTURE_H

#include "resource.h"

#include <SDL2/SDL_render.h>

#include <string>

namespace worms
{
    class Texture : public Resource
    {
    public:
        struct Info
        {
            Uint32 format;
            int access;
            int w;
            int h;
        };

    private:
        SDL_Texture* handle;

    public:
        static Texture create(const SDL_Renderer*       sdlRenderer,
                              Uint32                    format,
                              int                       access,
                              int                       width,
                              int                       height);

        static Texture convert(const SDL_Renderer*          sdlRenderer,
                               const SDL_Surface*           sdlSurface);

        explicit Texture(SDL_Texture* sdlTexture) noexcept : handle{sdlTexture} {}
        Texture(Texture&& texture) noexcept;
        ~Texture();

        Texture& operator=(Texture&& texture) noexcept;

        Info requestInfo() const noexcept;

        const auto* getHandle() const noexcept {return handle;}
    };
}

#endif
