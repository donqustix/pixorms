#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <SDL2/SDL_rect.h>

#include <unordered_map>
#include <string>

namespace worms
{
    class ResourceContainer;
    class Texture;
    class Config;

    class TextureAtlas
    {
        std::unordered_map<std::string, SDL_Rect> areas;
        const Texture* texture;

    public:
        static TextureAtlas load(const Config& config, const Texture& texture);

        TextureAtlas(std::unordered_map<std::string, SDL_Rect> areas, const Texture* texture);

        SDL_Rect findArea(const std::string& name) const;

        const auto& getTexture() const noexcept {return *texture;}
    };
}

#endif
