#ifndef WEAPON_H
#define WEAPON_H

#include "texture.h"

#include <SDL2/SDL_rect.h>

namespace worms
{
    struct Weapon
    {
        SDL_Rect             area;
        const Texture*       texture;
        int                  type;
        int                  count;
    };
}

#endif
