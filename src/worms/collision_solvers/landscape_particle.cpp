#include "landscape_particle.h"

#include "worms/landscape.h"
#include "worms/particle.h"
#include "worms/surface.h"

#include <cmath>

using worms::collision_solvers::LandscapeParticle;

void LandscapeParticle::solve(GameObject& gm1, GameObject& gm2) const
{
    auto& landscape = dynamic_cast<Landscape&>(gm1);
    auto& particle  = dynamic_cast<Particle &>(gm2);

    if (particle.fx < 0 || particle.fx >= Landscape::WIDTH ||
        particle.fy < 0 || particle.fy >= Landscape::WIDTH)
        return;

    const bool mustLock = SDL_MUSTLOCK(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));
    if (mustLock)
        ::SDL_LockSurface(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));

    const float sx = particle.fx - particle.x;
    const float sy = particle.fy - particle.y;

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
            particle.fx = particle.x + ix;
            particle.fy = particle.y + iy;

            if (landscape.getPixel(particle.fy, particle.fx))
                particle.kill();

            ix += dsx;
            iy += dsy;
        }
    }
    else
    {
        if (landscape.getPixel(particle.fy, particle.fx))
            particle.kill();
    }

    if (mustLock)
        ::SDL_UnlockSurface(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));
}

