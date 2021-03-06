#include "surface.h"

#include "worms/config_block.h"
#include "worms/surface.h"
#include "worms/application.h"
#include "worms/resource_container.h"

using worms::resource_loaders::Surface;

void Surface::load(Application& application, const ConfigBlock& block) const
{
    ResourceContainer& resourceContainer = application.getResourceContainer();

    for (const auto& rv : block.variables)
    {
        auto surface = worms::Surface::convert(worms::Surface::load(rv.second).getHandle(), SDL_PIXELFORMAT_RGBA32);
        resourceContainer.insert<worms::Surface>("surface_" + rv.first, std::move(surface));
    }
}

