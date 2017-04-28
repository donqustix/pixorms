#ifndef RESOURCELOADERFONT_H
#define RESOURCELOADERFONT_H

#include "worms/resource_loader.h"

namespace worms
{
    namespace resource_loaders
    {
        struct Font;
    }

    struct resource_loaders::Font : ResourceLoader
    {
        void load(Application& application, const ConfigBlock& block) const override;
    };
}

#endif
