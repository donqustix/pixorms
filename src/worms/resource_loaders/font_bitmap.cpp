#include "font_bitmap.h"

#include "worms/config_block.h"
#include "worms/font_bitmap.h"
#include "worms/font.h"
#include "worms/resource_container.h"
#include "worms/application.h"
#include "worms/utility.h"
#include "worms/graphics.h"

using worms::resource_loaders::FontBitmap;

void FontBitmap::load(Application& application, const ConfigBlock& block) const
{
    ResourceContainer& resourceContainer = application.getResourceContainer();

    for (const auto& rv : block.variables)
    {
        resourceContainer.insert<worms::FontBitmap>("font_bitmap_" + rv.first,
                worms::FontBitmap::generate(Font::load(rv.second,
                        utility::convert<int>(rv.first.substr(rv.first.find('_') + 1))),
                    application.getGraphics().getSdlRenderer()));
    }
}

