#ifndef RESOURCELOADERSURFACE_H
#define RESOURCELOADERSURFACE_H

#include "worms/resource_loader.h"

namespace worms
{
    namespace resource_loaders
    {
        struct Surface;
    }

    struct resource_loaders::Surface : ResourceLoader
    {
        void load(Application& application, const ConfigBlock& block) const override;
    };
}

#endif
