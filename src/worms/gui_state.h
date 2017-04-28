#ifndef GUISTATE_H
#define GUISTATE_H

#include <SDL2/SDL_events.h>

namespace worms
{
    class Graphics;

    struct GuiState
    {
        virtual ~GuiState() = default;

        virtual void update(unsigned delta) = 0;
        virtual void render(Graphics& graphics) = 0;
        virtual void handle(const SDL_Event& sdlEvent) = 0;
    };
}

#endif
