#include "landscape_worm.h"

#include "worms/landscape.h"
#include "worms/worm.h"
#include "worms/surface.h"

#include <cmath>

using worms::collision_solvers::LandscapeWorm;

void LandscapeWorm::solve(GameObject& gm1, GameObject& gm2) const
{
    auto& landscape = dynamic_cast<Landscape&>(gm1);
    auto& worm      = dynamic_cast<Worm     &>(gm2);

    if (worm.fx < 0 || worm.fx + Worm::SIZE / 2 >= Landscape::WIDTH ||
        worm.fy < 0 || worm.fy + Worm::SIZE - 1 >= Landscape::WIDTH)
        return;

    const bool mustLock = SDL_MUSTLOCK(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));
    if (mustLock)
        ::SDL_LockSurface(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));

    const float sx = worm.fx - worm.x;
    const float sy = worm.fy - worm.y;

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
            const float tfx = worm.fx = worm.x + ix;
            const float tfy = worm.fy = worm.y + iy;

            if      (landscape.getPixel(worm.fy + Worm::SIZE / 2, worm.fx + Worm::SIZE / 2 - 1))
                worm.fx = worm.x + ++ix;
            else if (landscape.getPixel(worm.fy + Worm::SIZE / 2, worm.fx + Worm::SIZE / 2    ))
                worm.fx = worm.x + --ix;
            else
                ix += dsx;

            if      (landscape.getPixel(worm.fy + Worm::SIZE - 1, worm.fx + Worm::SIZE / 2    ))
                worm.fy = worm.y + --iy;
            else if (landscape.getPixel(worm.fy                 , worm.fx + Worm::SIZE / 2    ))
                worm.fy = worm.y + ++iy;
            else
                iy += dsy;

            if (worm.fx != tfx || worm.fy != tfy) worm.currentState = Worm::MOVEMENT;
        }
    }
    else
    {
        const float tfx = worm.fx;
        const float tfy = worm.fy;

        for (; landscape.getPixel(worm.fy + Worm::SIZE / 2, worm.fx + Worm::SIZE / 2 - 1); ++worm.fx);
        for (; landscape.getPixel(worm.fy + Worm::SIZE / 2, worm.fx + Worm::SIZE / 2    ); --worm.fx);
        for (; landscape.getPixel(worm.fy + Worm::SIZE - 1, worm.fx + Worm::SIZE / 2    ); --worm.fy);
        for (; landscape.getPixel(worm.fy                 , worm.fx + Worm::SIZE / 2    ); ++worm.fy);

        if (worm.fx != tfx || worm.fy != tfy) worm.currentState = Worm::MOVEMENT;
    }

    if (mustLock)
        ::SDL_UnlockSurface(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));
}
