#include "graphics.h"
#include "font_bitmap.h"
#include "window.h"

#include <stdexcept>
#include <utility>

using worms::Graphics;

Graphics Graphics::create(const Window& window, int virtualWidth, int virtualHeight)
{
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> sdlRenderer{
        [&window] {
            SDL_Renderer* const handle =
                ::SDL_CreateRenderer(const_cast<SDL_Window*>(window.getHandle()), -1, SDL_RENDERER_ACCELERATED);
            if (!handle)
                throw std::runtime_error{::SDL_GetError()};
            return handle;
        }(),
        ::SDL_DestroyRenderer
    };
    ::SDL_RenderSetLogicalSize(sdlRenderer.get(), virtualWidth, virtualHeight);
    
    return Graphics{std::move(sdlRenderer)};
}

Graphics::Graphics(std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> sdlRenderer) : 
    sdlRenderer{std::move(sdlRenderer)}
{
}

Graphics::Graphics(Graphics&&) noexcept = default;

Graphics::~Graphics() = default;

Graphics& Graphics::operator=(Graphics&&) noexcept = default;

void Graphics::setColor(Uint32 color) noexcept
{
    ::SDL_SetRenderDrawColor(sdlRenderer.get(),  color        & 0xFF,
                                                (color >>  8) & 0xFF,
                                                (color >> 16) & 0xFF,
                                                (color >> 24) & 0xFF);
}

void Graphics::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const noexcept
{
    struct{Uint8 r, g, b, a;} temp;
    ::SDL_GetRenderDrawColor(sdlRenderer.get(), &temp.r, &temp.g, &temp.b, &temp.a);
    ::SDL_SetRenderDrawColor(sdlRenderer.get(), r, g, b, a);
    ::SDL_RenderClear(sdlRenderer.get());
    ::SDL_SetRenderDrawColor(sdlRenderer.get(), temp.r, temp.g, temp.b, temp.a);
}

void Graphics::drawText(const FontBitmap& fontBitmap, const std::string& str, int x, int y) const noexcept
{
    for (std::string::size_type i = 0; i < str.length(); ++i)
    {
        const int sx = x + i * fontBitmap.symbolSize;
        const int cx = (str[i] - FontBitmap::BEG) * fontBitmap.symbolSize;
        drawTexture(fontBitmap.texture,
            {sx, y, fontBitmap.symbolSize, fontBitmap.symbolSize},
            {cx, 0, fontBitmap.symbolSize, fontBitmap.symbolSize});
    }
}

void Graphics::drawTexture(const Texture& texture, SDL_Rect dstrect, SDL_Rect srcrect) const noexcept
{
    ::SDL_RenderCopy(sdlRenderer.get(), const_cast<SDL_Texture*>(texture.getHandle()), &srcrect, &dstrect);
}

void Graphics::drawTexture(const Texture& texture, SDL_Rect dstrect) const noexcept
{
    ::SDL_RenderCopy(sdlRenderer.get(), const_cast<SDL_Texture*>(texture.getHandle()), nullptr, &dstrect);
}

void Graphics::drawTexture(const Texture& texture, SDL_Rect dstrect, SDL_Rect srcrect, double angle,
        SDL_RendererFlip flip) const noexcept
{
    ::SDL_RenderCopyEx(sdlRenderer.get(), const_cast<SDL_Texture*>(texture.getHandle()),
            &srcrect, &dstrect, angle, nullptr, flip);
}

void Graphics::fillRect(int x, int y, int w, int h) const noexcept
{
    const SDL_Rect dstrect{x, y, w, h};
    ::SDL_RenderFillRect(sdlRenderer.get(), &dstrect);
}

void Graphics::drawPoint(int x, int y) const noexcept
{
    ::SDL_RenderDrawPoint(sdlRenderer.get(), x, y);
}

void Graphics::drawLine(int x1, int y1, int x2, int y2) const noexcept
{
    ::SDL_RenderDrawLine(sdlRenderer.get(), x1, y1, x2, y2);
}

Graphics::VirtualSize Graphics::requestVirtualSize() const noexcept
{
    int w, h;
    ::SDL_RenderGetLogicalSize(sdlRenderer.get(), &w, &h);
    return {w, h};
}


