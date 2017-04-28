#include "font.h"

#include "worms/config_block.h"
#include "worms/application.h"
#include "worms/resource_container.h"
#include "worms/utility.h"
#include "worms/font.h"

using worms::resource_loaders::Font;

void Font::load(Application& application, const ConfigBlock& block) const
{
    ResourceContainer& resourceContainer = application.getResourceContainer();

    for (const auto& rv : block.variables)
        resourceContainer.insert<worms::Font>("font_" + rv.first, worms::Font::load(rv.second,
                    utility::convert<int>(rv.first.substr(rv.first.find('_') + 1))));
}

