#ifndef SURFACE_H
#define SURFACE_H

#include "resource.h"

#include <SDL2/SDL_surface.h>

#include <string>

namespace worms
{
    class Surface : public Resource
    {
        SDL_Surface* handle;

    public:
        static Surface create(int w, int h, int depth, Uint32 format);

        static Surface convert(const SDL_Surface*       sdlSurface,
                               Uint32                   format);

        static Surface load(const std::string& filepath);

        explicit Surface(SDL_Surface* sdlSurface) noexcept : handle{sdlSurface} {}
        Surface(Surface&& surface) noexcept;
        ~Surface();

        Surface& operator=(Surface&& surface) noexcept;

        void fillCircle(int x0, int y0, int radius, Uint32 color) noexcept;

        void setPixel(int row, int col, Uint32 pixel) noexcept
        {
            static constexpr void(Surface::*functions[4])(int, int, Uint32)
            {
                &Surface::setPixel8,
                &Surface::setPixel16,
                &Surface::setPixel24,
                &Surface::setPixel32
            };
            (this->*functions[handle->format->BytesPerPixel - 1])(row, col, pixel);
        }

        Uint32 makePixel(Uint32 rgba) const noexcept
        {
            return ::SDL_MapRGBA(handle->format,  rgba        & 0xFF,
                                                 (rgba >>  8) & 0xFF,
                                                 (rgba >> 16) & 0xFF,
                                                 (rgba >> 24) & 0xFF);
        }

        Uint32 getRGB(Uint32 pixel) const noexcept
        {
            Uint8 r, g, b;
            ::SDL_GetRGB(pixel, handle->format, &r, &g, &b);
            return r | g << 8 | b << 16;
        }

        Uint32 getPixel(int row, int col) const noexcept
        {
            static constexpr Uint32(Surface::*functions[4])(int, int) const
            {
                &Surface::getPixel8,
                &Surface::getPixel16,
                &Surface::getPixel24,
                &Surface::getPixel32
            };
            return (this->*functions[handle->format->BytesPerPixel - 1])(row, col);
        }

        void setPixel32(int row, int col, Uint32 pixel) noexcept
        {
            *(static_cast<Uint32*>(handle->pixels) + row * handle->w + col) = pixel;
        }

        void setPixel24(int row, int col, Uint32 pixel) noexcept
        {
            union
            {
                struct {Uint8 c1, c2, c3;} pd;
                Uint32 value;
            };
            value = pixel;
            *reinterpret_cast<decltype(pd)*>(static_cast<Uint8*>(handle->pixels) + 3 * row * handle->w + 3 * col) = pd;
        }

        void setPixel16(int row, int col, Uint32 pixel) noexcept
        {
            *(static_cast<Uint16*>(handle->pixels) + row * handle->w + col) = pixel;
        }

        void setPixel8(int row, int col, Uint32 pixel) noexcept
        {
            *(static_cast<Uint8*>(handle->pixels) + row * handle->w + col) = pixel;
        }

        Uint32 getPixel32(int row, int col) const noexcept
        {
            return *(static_cast<Uint32*>(handle->pixels) + row * handle->w + col);
        }

        Uint32 getPixel24(int row, int col) const noexcept
        {
            return *reinterpret_cast<Uint32*>(static_cast<Uint8*>(handle->pixels) + 
                    3 * row * handle->w + 3 * col) & 0xFFFFFF;
        }

        Uint32 getPixel16(int row, int col) const noexcept
        {
            return *(static_cast<Uint16*>(handle->pixels) + row * handle->w + col) & 0xFFFF;
        }

        Uint32 getPixel8(int row, int col) const noexcept
        {
            return *(static_cast<Uint8 *>(handle->pixels) + row * handle->w + col) & 0xFF;
        }

        const auto* getHandle() const noexcept {return handle;}
    };
}

#endif
