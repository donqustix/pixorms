#include "texture.h"

#include "worms/config_block.h"
#include "worms/surface.h"
#include "worms/resource_container.h"
#include "worms/texture.h"
#include "worms/application.h"
#include "worms/graphics.h"

using worms::resource_loaders::Texture;

void Texture::load(Application& application, const ConfigBlock& block) const
{
    ResourceContainer& resourceContainer = application.getResourceContainer();

    for (const auto& rv : block.variables)
    {
        auto surface = Surface::convert(Surface::load(rv.second).getHandle(), SDL_PIXELFORMAT_RGBA32);
        resourceContainer.insert<worms::Texture>("texture_" + rv.first,
                worms::Texture::convert(application.getGraphics().getSdlRenderer(), surface.getHandle()));
    }
}

