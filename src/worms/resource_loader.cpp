#include "resource_loader.h"
#include "config.h"
#include "resource_container.h"
#include "texture.h"
#include "font_bitmap.h"
#include "font.h"
#include "application.h"
#include "graphics.h"
#include "surface.h"
#include "window.h"

void worms::resource_loader::load(Application& application, const Config& config)
{
    ResourceContainer& resourceContainer = application.getResourceContainer();

    for (const auto& b : config.getMainBlock().blocks)
    {
        if (b.first == "textures")
        {
            for (const auto& rv : b.second.variables)
            {
                auto surface = Surface::load(rv.second);
                surface.setColorKey(surface.makePixel(0xFF00FF));
                resourceContainer.insert<Texture>("texture_" + rv.first,
                        Texture::convert(application.getGraphics().getSdlRenderer(), surface.getHandle()));
            }
        }
        else if (b.first == "fonts")
        {
            for (const auto& rv : b.second.variables)
                resourceContainer.insert<Font>("font_" + rv.first, Font::load(rv.second,
                            utility::convert<int>(rv.first.substr(rv.first.find('_') + 1))));
        }
        else if (b.first == "surfaces")
        {
            for (const auto& rv : b.second.variables)
            {
                auto surface = Surface::load(rv.second);
                surface.setColorKey(surface.makePixel(0xFF00FF));
                resourceContainer.insert<Surface>("surface_" + rv.first, std::move(surface));
            }
        }
        else if (b.first == "font_bitmaps")
        {
            for (const auto& rv : b.second.variables)
            {
                resourceContainer.insert<FontBitmap>("font_bitmap_" + rv.first,
                        FontBitmap::generate(Font::load(rv.second,
                                utility::convert<int>(rv.first.substr(rv.first.find('_') + 1))),
                            application.getWindow().requestVideoInfo(), application.getGraphics().getSdlRenderer()));
            }
        }
    }
}

