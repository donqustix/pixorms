#include "button_factory.h"
#include "texture_atlas.h"
#include "config.h"
#include "resource_container.h"
#include "application.h"
#include "font_bitmap.h"
#include "gui_button.h"
#include "graphics.h"

#include <utility>

using worms::ButtonFactory;
using worms::GuiButton;

ButtonFactory::ButtonFactory(Application& application)
{
    textureAtlas =
        std::make_unique<TextureAtlas>(TextureAtlas::load(Config::parseFile("res/textures/buttons.cfg"),
            *application.getResourceContainer().find<Texture>("texture_buttons")));
    fontBitmap = application.getResourceContainer().find<FontBitmap>("font_bitmap_fixedsys_8");
    
    const Graphics::VirtualSize virtualSize = application.getGraphics().requestVirtualSize();
    const SDL_Rect areaReleased = textureAtlas->findArea("released");

    buttonInfo = {virtualSize.w >> 1, virtualSize.h >> 1, areaReleased.w, areaReleased.h};
}

ButtonFactory::ButtonFactory(ButtonFactory&&) noexcept = default;

ButtonFactory::~ButtonFactory() = default;

ButtonFactory& ButtonFactory::operator=(ButtonFactory&&) noexcept = default;

std::unique_ptr<GuiButton> ButtonFactory::makeButton(const std::string&        name,
                                                     int                       x,
                                                     int                       y,
                                                     int                       w,
                                                     int                       h,
                                                     std::function<void()>     action) const
{
    return std::make_unique<GuiButton>(
            GuiButton::create(*textureAtlas, std::move(action), std::move(name), {x, y, w, h}, fontBitmap)
    );
}

