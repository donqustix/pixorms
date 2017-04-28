#include "resource_loader_list.h"
#include "resource_loader.h"
#include "config.h"

#include "resource_loaders/font.h"
#include "resource_loaders/font_bitmap.h"
#include "resource_loaders/surface.h"
#include "resource_loaders/texture.h"

using worms::ResourceLoaderList;

using worms::resource_loaders::Font;
using worms::resource_loaders::Texture;
using worms::resource_loaders::FontBitmap;
using worms::resource_loaders::Surface;

ResourceLoaderList::ResourceLoaderList()
{
    loaders.emplace("fonts"         , std::make_unique<Font      >());
    loaders.emplace("font_bitmaps"  , std::make_unique<FontBitmap>());
    loaders.emplace("surfaces"      , std::make_unique<Surface   >());
    loaders.emplace("textures"      , std::make_unique<Texture   >());
}

ResourceLoaderList::ResourceLoaderList(ResourceLoaderList&&) noexcept = default;

ResourceLoaderList::~ResourceLoaderList() = default;

ResourceLoaderList& ResourceLoaderList::operator=(ResourceLoaderList&&) noexcept = default;

void ResourceLoaderList::load(Application& application, const Config& config) const
{
    for (const auto& b : config.getMainBlock().blocks)
        loaders.find(b.first)->second->load(application, b.second);
}

