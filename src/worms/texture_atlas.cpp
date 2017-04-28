#include "texture_atlas.h"
#include "config.h"

#include <stdexcept>

using worms::TextureAtlas;

TextureAtlas TextureAtlas::load(const Config& config, const Texture& texture)
{
    std::unordered_map<std::string, SDL_Rect> areas;
    for (const auto& b : 
               config.getMainBlock().blocks)
    {
        const auto x = config.findValue<int>("x", b.second);
        const auto y = config.findValue<int>("y", b.second);
        const auto w = config.findValue<int>("w", b.second);
        const auto h = config.findValue<int>("h", b.second);

        areas.emplace(b.first, SDL_Rect{x, y, w, h});
    }

    return TextureAtlas{std::move(areas), &texture};
}

TextureAtlas::TextureAtlas(std::unordered_map<std::string, SDL_Rect> areas, const Texture* texture) :
    areas{std::move(areas)}, texture{texture} {}

SDL_Rect TextureAtlas::findArea(const std::string& name) const
{
    const auto iter = areas.find(name);
    if (iter == areas.cend())
        throw std::runtime_error{"there is no the area " + name + " in the texture atlas"};
    return iter->second;
}

