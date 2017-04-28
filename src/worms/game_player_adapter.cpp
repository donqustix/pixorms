#include "game_player_adapter.h"
#include "worm.h"
#include "weapon_list.h"
#include "player.h"

#include "gui_states/game.h"

using worms::GamePlayerAdapter;
using worms::Worm;
using worms::Camera;

using worms::gui_states::Game;

void GamePlayerAdapter::setWeapon(int type) const noexcept
{
    Game::PlayerData& playerData = game->playersData[game->currentPlayerIndex];
    Weapon& weapon = playerData.weaponList->findWeapon(static_cast<WeaponList::Types>(type));
    if (weapon.count)
        playerData.worms[playerData.currentWormIndex]->setWeapon(&weapon);
}

void GamePlayerAdapter::useWeapon() const
{
    Game::PlayerData& playerData = game->playersData[game->currentPlayerIndex];
    playerData.worms[playerData.currentWormIndex]->useWeapon(*game);
}

void GamePlayerAdapter::moveWorm(unsigned delta, bool side) const noexcept
{
    Game::PlayerData& playerData = game->playersData[game->currentPlayerIndex];
    playerData.worms[playerData.currentWormIndex]->move(delta, side);
}

void GamePlayerAdapter::rotateWormDirection(unsigned delta, bool side) const noexcept
{
    Game::PlayerData& playerData = game->playersData[game->currentPlayerIndex];
    playerData.worms[playerData.currentWormIndex]->rotate(delta, side);
}

void GamePlayerAdapter::punch(float nx, float ny, float flySpeed) const noexcept
{
    Game::PlayerData& playerData = game->playersData[game->currentPlayerIndex];
    playerData.worms[playerData.currentWormIndex]->punch(nx, ny, flySpeed);
}

const Camera& GamePlayerAdapter::getCamera() const noexcept
{
    return game->camera;
}

const Worm* GamePlayerAdapter::getWorm() const noexcept
{
    Game::PlayerData& playerData = game->playersData[game->currentPlayerIndex];
    return playerData.worms[playerData.currentWormIndex].get();
}

