#ifndef GUISTATEMAINMENU_H
#define GUISTATEMAINMENU_H

#include "worms/gui_state.h"

#include <memory>
#include <vector>

namespace worms
{
    class Application;
    class GuiButton;

    namespace gui_states
    {
        class MainMenu;
    }

    class gui_states::MainMenu : public GuiState
    {
        std::vector<std::unique_ptr<GuiButton>> buttons;

    public:
        explicit MainMenu(Application& application);
        MainMenu(MainMenu&&) noexcept;
        ~MainMenu();

        MainMenu& operator=(MainMenu&&) noexcept;

        void update(unsigned delta) override;
        void render(Graphics& graphics) override;
        void handle(const SDL_Event& sdlEvent) override;
    };
}

#endif
