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

    adapter.destroy(100, 100, 100);

    for (int i = 0; i < 8; ++i)
        adapter.destroy(100 + (i + 1) * 50, 100 + i * 5 * i, 100);
}

