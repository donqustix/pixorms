#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL_rect.h>

#include <vector>

namespace worms
{
    class Graphics;
    class Texture;
    class Config;

    class Animation
    {
        std::vector<SDL_Rect>       areas;
        const Texture*              texture;
        unsigned                    index               = 0;
        int                         lastFrameTime       = 0;

    public:
        static Animation load(const Config& config, const Texture& texture);

        Animation(std::vector<SDL_Rect> areas, const Texture* texture);

        void render(Graphics& graphics, int x, int y, int size, bool flip = false, double angle = 0.0) const noexcept;
        void update(unsigned delta, int time) noexcept;
    };
}

#endif
