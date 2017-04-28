#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <SDL2/SDL_events.h>

#include <functional>
#include <string>
#include <array>

namespace worms
{
    struct FontBitmap;

    class TextureAtlas;
    class Graphics;
    class Texture;

    class GuiButton
    {
        enum States
        {
            PRESSED, RELEASED, SELECTED
        };

        std::function<void()>       action;
        std::string                 name;
        std::array<SDL_Rect, 3>     areas;
        SDL_Rect                    boundingBox;
        const Texture*              texture;
        const FontBitmap*           fontBitmap;

        States currentState = RELEASED;

        bool enabled = false;

    public:
        static GuiButton create(const TextureAtlas&         textureAtlas,
                                std::function<void()>       action,
                                std::string                 name,
                                SDL_Rect                    boundingBox,
                                const FontBitmap*           fontBitmap);

        GuiButton(std::function<void()>         action,
                  std::string                   name,
                  std::array<SDL_Rect, 3>       areas,
                  SDL_Rect                      boundingBox,
                  const Texture*                texture,
                  const FontBitmap*             fontBitmap);

        void render(Graphics& graphics) const;
        void handle(const SDL_Event& sdlEvent);

        const auto& getName() const noexcept {return name;}
        const auto& getBoundingBox() const noexcept {return boundingBox;}
        auto getCurrentState() const noexcept {return currentState;}
    };
}

#endif
