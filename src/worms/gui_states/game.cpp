#include "game.h"

#include "worms/landscape_generators/sandy.h"

#include "worms/landscape.h"
#include "worms/player.h"
#include "worms/worm.h"
#include "worms/graphics.h"
#include "worms/resource_container.h"
#include "worms/application.h"
#include "worms/window.h"
#include "worms/bullet.h"
#include "worms/texture_atlas.h"
#include "worms/texture.h"
#include "worms/config.h"
#include "worms/particle.h"
#include "worms/game_player_adapter.h"
#include "worms/weapon_list.h"
#include "worms/bullet_factory.h"
#include "worms/collision_solver_list.h"

#include <algorithm>
#include <utility>
#include <cmath>
#include <iterator>

using worms::gui_states::Game;

Game::Game(Application& application)
{
    bulletFactory = std::make_unique<BulletFactory>(std::make_unique<TextureAtlas>(
                TextureAtlas::load(Config::parseFile("res/textures/bullets.cfg"), *application.getResourceContainer().
                    find<Texture>("texture_bullets"))));

    landscape = std::make_unique<Landscape>(Landscape::create(application.getWindow().requestVideoInfo()));
    landscape->applyGeneration(landscape_generators::Sandy{application.getResourceContainer()});

    collisionSolverList = std::make_unique<CollisionSolverList>();
}

Game::Game(Game&&) noexcept = default;

Game::~Game() = default;

Game& Game::operator=(Game&&) noexcept = default;

void Game::update(unsigned delta)
{
    for (auto& b : bullets)
    {
        collisionSolverList->solve(*landscape, *b);
        b->update(delta);

        if (b->isParticleReady())
        {
            std::vector<std::unique_ptr<Particle>> bulletParticles{b->pickUpParticles()};
        
            particles.insert(particles.end(), std::make_move_iterator(bulletParticles.begin()),
                                              std::make_move_iterator(bulletParticles.end()));
        }
        if (b->isKilled())
        {
            for (auto& pd : playersData)
            {
                for (auto& w : pd.second.worms)
                {
                    const float sx = w->getX() - b->getX() + (Worm::SIZE - b->getSize()) / 2;
                    const float sy = w->getY() - b->getY() - (Worm::SIZE - b->getSize()) / 2;

                    const float distance = std::sqrt(sx * sx + sy * sy);

                    if (distance < b->getDamage())
                    {
                        const float invDistance = 1.0F / distance;
                        const float nx = sx * invDistance;
                        const float ny = sy * invDistance;

                        w->takeDamage(b->getDamage() * b->getDamage() / distance);
                        w->punch(nx, ny);
                    }
                }
            }
        }
    }

    const PlayerData& playerData = playersData[currentPlayerIndex];
    playerData.player->update(GamePlayerAdapter{this}, delta);

    collisionSolverList->solve(*landscape, *playerData.worms[playerData.currentWormIndex]);
    playerData.worms[playerData.currentWormIndex]->update(delta);

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](auto& b) {
        return b->isKilled();
    }), bullets.end());

    for (auto& p : particles)
    {
        collisionSolverList->solve(*landscape, *p);
        p->update(delta);
    }

    particles.erase(std::remove_if(particles.begin(), particles.end(), [](auto& p) {
        return p->isKilled();
    }), particles.end());
}

void Game::render(Graphics& graphics)
{
    const PlayerData& playerData = playersData[currentPlayerIndex];

    const Graphics::VirtualSize virtualSize = graphics.requestVirtualSize();

    camera.x = playerData.worms[playerData.currentWormIndex]->getX() - (virtualSize.w - Worm::SIZE) / 2;
    camera.y = playerData.worms[playerData.currentWormIndex]->getY() - (virtualSize.h - Worm::SIZE) / 2;

    landscape->render(graphics, camera);

    playerData.worms[playerData.currentWormIndex]->render(graphics, camera);

    for (const auto& p : particles)
        p->render(graphics, camera);

    for (const auto& b : bullets)
        b->render(graphics, camera);
}

void Game::handle(const SDL_Event& sdlEvent)
{
    if (playersData[currentPlayerIndex].player->getType() == PlayerTypes::BRAIN)
        playersData[currentPlayerIndex].player->handle(sdlEvent);
}

void Game::setLandscape(std::unique_ptr<Landscape> landscape)
{
    this->landscape = std::move(landscape);
}

void Game::addPlayerData(PlayerData playerData, int team)
{
    playersData.emplace(team, std::move(playerData));
}

void Game::addBullet(float x, float y, float nx, float ny, int weaponType)
{
    bullets.push_back(bulletFactory->makeBullet(x, y, nx, ny, weaponType));
}

