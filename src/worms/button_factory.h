#ifndef BUTTONFACTORY_H
#define BUTTONFACTORY_H

#include <SDL2/SDL_rect.h>

#include <functional>
#include <memory>
#include <string>

namespace worms
{
    class TextureAtlas;
    class GuiButton;
    class FontBitmap;
    class Application;

    class ButtonFactory
    {
        std::unique_ptr<TextureAtlas>   textureAtlas;
        SDL_Rect                        buttonInfo;
        const FontBitmap*               fontBitmap;

    public:
        explicit ButtonFactory(Application& application);
        ButtonFactory(ButtonFactory&&) noexcept;
        ~ButtonFactory();

        ButtonFactory& operator=(ButtonFactory&&) noexcept;

        std::unique_ptr<GuiButton> makeButton(const std::string&        name,
                                              int                       x,
                                              int                       y,
                                              int                       w,
                                              int                       h,
                                              std::function<void()>     action) const;

        const auto& getTextureAtlas() const noexcept {return *textureAtlas;}
        const auto& getButtonInfo() const noexcept {return buttonInfo;}
    };
}

#endif
