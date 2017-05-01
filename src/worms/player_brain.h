#ifndef PLAYERBRAIN_H
#define PLAYERBRAIN_H

#include "player.h"

#include <SDL2/SDL_scancode.h>

namespace worms
{
    class PlayerBrain : public Player
    {
        bool        keyStates[SDL_NUM_SCANCODES]{};
        bool        rotationSide;

    public:
        PlayerBrain() noexcept;

        void update(const GamePlayerAdapter& adapter, unsigned delta) override;
        void handle(const SDL_Event& sdlEvent) override;
    };
}

#endif
