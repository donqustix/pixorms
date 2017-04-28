#ifndef RESOURCELOADERFONTBITMAP_H
#define RESOURCELOADERFONTBITMAP_H

#include "worms/resource_loader.h"

namespace worms
{
    namespace resource_loaders
    {
        struct FontBitmap;
    }

    struct resource_loaders::FontBitmap : ResourceLoader
    {
        void load(Application& application, const ConfigBlock& block) const override;
    };
}

#endif
