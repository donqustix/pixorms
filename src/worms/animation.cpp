#include "animation.h"
#include "graphics.h"
#include "config.h"

#include <utility>

using worms::Animation;

Animation Animation::load(const Config& config, const Texture& texture)
{
    std::vector<SDL_Rect> areas;
    for (const auto& bp : config.getMainBlock().blocks)
    {
        const int x = config.findValue<int>("x", bp.second);
        const int y = config.findValue<int>("y", bp.second);
        const int w = config.findValue<int>("w", bp.second);
        const int h = config.findValue<int>("h", bp.second);

        areas.push_back({x, y, w, h});
    }

    return {std::move(areas), &texture};
}

Animation::Animation(std::vector<SDL_Rect> areas, const Texture* texture) :
    areas{std::move(areas)}, texture{texture}
{
}

void Animation::render(Graphics& graphics, int x, int y, int size, bool flip, double angle) const noexcept
{
    graphics.drawTexture(*texture, {x, y, size, size}, areas[index], angle, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Animation::update(unsigned delta, int time) noexcept
{
    lastFrameTime += delta;

    if (lastFrameTime >= time)
    {
        lastFrameTime = 0;
        if (++index == areas.size())
              index = 0;
    }
}

