#ifndef PLAYER_H
#define PLAYER_H

#include "player_types.h"

#include <SDL2/SDL_events.h>

namespace worms
{
    class GamePlayerAdapter;

    class Player
    {
        PlayerTypes type;

    public:
        explicit Player(PlayerTypes type) noexcept : type{type} {}
        virtual ~Player() = default;

        virtual void update(GamePlayerAdapter& adapter, unsigned delta) {}
        virtual void handle(const SDL_Event& sdlEvent) {}

        auto getType() const noexcept {return type;}
    };
}

#endif
