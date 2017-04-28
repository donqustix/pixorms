#include "player_brain.h"
#include "game_player_adapter.h"
#include "weapon_list.h"

using worms::PlayerBrain;

PlayerBrain::PlayerBrain() noexcept : Player{PlayerTypes::BRAIN} {}

void PlayerBrain::update(GamePlayerAdapter& adapter, unsigned delta)
{
    if      (keyStates[SDL_SCANCODE_A])
        adapter.moveWorm(delta, 0);
    else if (keyStates[SDL_SCANCODE_D])
        adapter.moveWorm(delta, 1);
    
    if (keyStates[SDL_SCANCODE_1])
        adapter.setWeapon(WeaponList::BAZOOKA);

    static bool fire = false;
    if (keyStates[SDL_SCANCODE_F])
        fire = true;
    else if (fire)
    {
        adapter.useWeapon();
        fire = false;
    }

    if (keyStates[SDL_SCANCODE_W] | keyStates[SDL_SCANCODE_S])
    {
        rotationSide = keyStates[SDL_SCANCODE_S];
        adapter.rotateWormDirection(delta, rotationSide);
    }

    if (keyStates[SDL_SCANCODE_P])
    {
        adapter.punch(0.7F, -0.7F, 80.0F / 1000.0F);
    }
}

void PlayerBrain::handle(const SDL_Event& sdlEvent)
{
    switch (sdlEvent.type)
    {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            keyStates[sdlEvent.key.keysym.scancode] = sdlEvent.type == SDL_KEYDOWN;
        break;
    }
}

