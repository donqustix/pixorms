#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_render.h>

#include <memory>
#include <string>

namespace worms
{
    struct FontBitmap;

    class Texture;
    class Window;

    class Graphics
    {
    public:
        struct VirtualSize
        {
            int w;
            int h;
        };

    private:
        std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> sdlRenderer;

    public:
        static Graphics create(const Window& window, int virtualWidth, int virtualHeight);

        Graphics(std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> sdlRenderer);
        Graphics(Graphics&& graphics) noexcept;
        ~Graphics();

        Graphics& operator=(Graphics&& graphics) noexcept;

        void setColor(Uint32 color) noexcept;
        void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF) const noexcept;
        void drawText(const FontBitmap& fontBitmap, const std::string& str, int x, int y) const noexcept;
        void drawTexture(const Texture& texture, SDL_Rect dstrect, SDL_Rect srcrect) const noexcept;
        void drawTexture(const Texture& texture, SDL_Rect dstrect) const noexcept;
        void drawTexture(const Texture& texture, SDL_Rect dstrect, SDL_Rect srcrect, double angle,
                SDL_RendererFlip = SDL_FLIP_NONE) const noexcept;
        void fillRect(int x, int y, int w, int h) const noexcept;
        void drawPoint(int x, int y) const noexcept;
        void drawLine(int x1, int y1, int x2, int y2) const noexcept;

        VirtualSize requestVirtualSize() const noexcept;

        const auto* getSdlRenderer() const noexcept {return sdlRenderer.get();}
    };
}

#endif
