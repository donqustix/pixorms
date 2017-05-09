#ifndef GAMEPREPARATION_H
#define GAMEPREPARATION_H

#include "worms/gui_state.h"

namespace worms
{
    namespace gui_states
    {
        class GamePreparation;
    }

    class Application;

    class gui_states::GamePreparation : public GuiState
    {
    public:
        explicit GamePreparation(Application& application);

        void update(unsigned delta) override;
        void render(Graphics& graphics) override;
        void handle(const SDL_Event& sdlEvent) override;
    };
}

#endif
