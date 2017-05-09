#include "landscape_bullet.h"

#include "worms/landscape.h"
#include "worms/bullet.h"
#include "worms/surface.h"

#include <cmath>

using worms::collision_solvers::LandscapeBullet;

void LandscapeBullet::solve(GameObject& gm1, GameObject& gm2) const
{
    auto& landscape = dynamic_cast<Landscape&>(gm1);
    auto& bullet    = dynamic_cast<Bullet   &>(gm2);

    if (bullet.fx + bullet.size / 2 < 0 || bullet.fx + bullet.size / 2 >= Landscape::WIDTH || 
        bullet.fy + bullet.size / 2 < 0 || bullet.fy + bullet.size / 2 >= Landscape::WIDTH)
        return;

    const bool mustLock = SDL_MUSTLOCK(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));
    if (mustLock)
        ::SDL_LockSurface(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));

    const float sx = bullet.fx - bullet.x;
    const float sy = bullet.fy - bullet.y;

    const float length = std::sqrt(sx * sx + sy * sy);
    if (length > 1.0F)
    {
        const float invLength = 1.0F / length;
        const float dsx = sx * invLength;
        const float dsy = sy * invLength;

        auto ix = 0.0F;
        auto iy = 0.0F;

        for (int i = 0; i < length; ++i)
        {
            bullet.fx = bullet.x + ix;
            bullet.fy = bullet.y + iy;

            const float cx = bullet.fx + bullet.size / 2;
            const float cy = bullet.fy + bullet.size / 2;

            if (landscape.getPixel(cy, cx))
            {
                landscape.destroy(cx, cy, bullet.damage >> 1);
                bullet.kill();
                break;
            }

            ix += dsx;
            iy += dsy;
        }
    }
    else
    {
        const float cx = bullet.fx + bullet.size / 2;
        const float cy = bullet.fy + bullet.size / 2;

        if (landscape.getPixel(cy, cx))
        {
            landscape.destroy(cx, cy, bullet.damage >> 1);
            bullet.kill();
        }
    }

    if (mustLock)
        ::SDL_UnlockSurface(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));
}

