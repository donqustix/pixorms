#include "sandy.h"

#include "worms/landscape_generator_adapter.h"
#include "worms/landscape.h"
#include "worms/resource_container.h"
#include "worms/surface.h"

using worms::landscape_generators::Sandy;

Sandy::Sandy(ResourceContainer& resourceContainer)
{
    surface = resourceContainer.find<Surface>("surface_land_0");
}

void Sandy::generate(const LandscapeGeneratorAdapter& adapter) const
{
    constexpr int scale = 2;

    const int w = surface->getHandle()->w * scale;
    const int h = surface->getHandle()->h * scale;

    for (int i = 0; i < Landscape::WIDTH; i += h)
    {
        for (int j = 0; j < Landscape::WIDTH; j += w)
        {
            adapter.drawSurface(*surface, i, j, w, h);
        }
    }

    const Landscape& landscape = adapter.getLandscape();

    const bool mustLock = SDL_MUSTLOCK(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));
    if (mustLock)
        ::SDL_LockSurface(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));

    adapter.fillCircle(100, 100, 100, landscape.getSurface().makePixel(0xFFFF00FF));

    for (int i = 0; i < 8; ++i)
        adapter.fillCircle(100 + (i + 1) * 50, 100 + i * 5 * i, 100, landscape.getSurface().makePixel(0xFFFF00FF));

    for (int i = 0; i < Landscape::WIDTH; ++i)
    {
        for (int j = 0; j < Landscape::WIDTH; ++j)
        {
            if (landscape.getPixel(i, j) == 0xFF00FF)
            {
                for (int k = 0; k < 5; ++k)
                {
                    if (i + k < Landscape::WIDTH && landscape.getPixel(i + k, j) != 0xFF00FF)
                        adapter.setPixel(i + k, j,
                                landscape.getSurface().makePixel(60 * (4 - k) << 8) + 10);
                }
            }
        }
    }

    if (mustLock)
        ::SDL_UnlockSurface(const_cast<SDL_Surface*>(landscape.getSurface().getHandle()));
}

