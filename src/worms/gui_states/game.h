#ifndef GUISTATEGAME_H
#define GUISTATEGAME_H

#include "worms/gui_state.h"
#include "worms/camera.h"

#include <unordered_map>
#include <vector>
#include <memory>

namespace worms
{
    class Application;
    class Landscape;
    class Player;
    class Particle;
    class Worm;
    class WeaponList;
    class BulletFactory;
    class Bullet;
    class CollisionSolverList;
    class GamePlayerAdapter;

    namespace gui_states
    {
        class Game;
    }

    class gui_states::Game : public GuiState
    {
        friend GamePlayerAdapter;

    public:
        struct PlayerData
        {
            std::vector<std::unique_ptr<Worm>>      worms;
            std::unique_ptr<Player>                 player;
            std::unique_ptr<WeaponList>             weaponList;
            unsigned                                currentWormIndex = 0;
        };
        
    private:
        std::unordered_map<int, PlayerData>             playersData;

        std::unique_ptr<BulletFactory>                  bulletFactory;

        std::unique_ptr<GamePlayerAdapter>              gamePlayerAdapter;
        std::unique_ptr<Landscape>                      landscape;

        std::unique_ptr<CollisionSolverList>            collisionSolverList;
        
        std::vector<std::unique_ptr<Bullet>>            bullets;
        std::vector<std::unique_ptr<Particle>>          particles;
        
        Camera                                          camera{};

        int                                             currentPlayerIndex = 0;
        
        bool                                            playerActivityDone = false;
        bool                                            side               = false;

    public:
        explicit Game(Application& application);
        Game(Game&&) noexcept;
        ~Game();

        Game& operator=(Game&&) noexcept;

        void update(unsigned delta) override;
        void render(Graphics& graphics) override;
        void handle(const SDL_Event& sdlEvent) override;

        void addPlayerData(PlayerData playerData, int team);

        void addBullet(float x, float y, float nx, float ny, int weaponType);

        void setLandscape(std::unique_ptr<Landscape> landscape);
    };
}

#endif
