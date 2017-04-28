#ifndef RESOURCELOADERTEXTURE_H
#define RESOURCELOADERTEXTURE_H

#include "worms/resource_loader.h"

namespace worms
{
    namespace resource_loaders
    {
        struct Texture;
    }

    struct resource_loaders::Texture : ResourceLoader
    {
        void load(Application& application, const ConfigBlock& block) const override;
    };
}

#endif
