#include "gui_button.h"
#include "font_bitmap.h"
#include "graphics.h"
#include "texture_atlas.h"

#include <utility>

using worms::GuiButton;

GuiButton GuiButton::create(const TextureAtlas&         textureAtlas,
                            std::function<void()>       action,
                            std::string                 name,
                            SDL_Rect                    boundingBox,
                            const FontBitmap*           fontBitmap)
{
    return 
    {
        std::move(action),
        std::move(name),
        {
            {
                textureAtlas.findArea("pressed"),
                textureAtlas.findArea("released"),
                textureAtlas.findArea("selected")
            }
        }, boundingBox, &textureAtlas.getTexture(), fontBitmap
    };
}

GuiButton::GuiButton(std::function<void()>         action,
                     std::string                   name,
                     std::array<SDL_Rect, 3>       areas,
                     SDL_Rect                      boundingBox,
                     const Texture*                texture,
                     const FontBitmap*             fontBitmap) :
    action{std::move(action)}, name {std::move(name )},
                               areas{std::move(areas)}, boundingBox{boundingBox}, texture   {texture   },
                                                                                  fontBitmap{fontBitmap}
{
}

void GuiButton::render(Graphics& graphics) const
{
    graphics.drawTexture(*texture, boundingBox, areas[currentState]);
    graphics.drawText(*fontBitmap, name, boundingBox.x + (boundingBox.w - fontBitmap->symbolSize * name.length()) / 2,
                                         boundingBox.y + (boundingBox.h - fontBitmap->symbolSize                ) / 2);
}

void GuiButton::handle(const SDL_Event& sdlEvent)
{
    const SDL_Point mousePoint{sdlEvent.button.x, sdlEvent.button.y};

    if (::SDL_PointInRect(&mousePoint, &boundingBox))
    {
        currentState = SELECTED;

        if (sdlEvent.button.state == SDL_PRESSED)
        {
            enabled = true;
            currentState = PRESSED;
        }
        else if (enabled)
        {
            enabled = false;
            action();
        }
    }
    else
        currentState = RELEASED;
}

