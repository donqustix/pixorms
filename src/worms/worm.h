#ifndef WORM_H
#define WORM_H

#include "game_object.h"
#include "worm_teams.h"

#include <memory>
#include <array>

//kamaabcd@ukr.net

namespace worms
{
    namespace collision_solvers
    {
        class LandscapeWorm;
    }

    namespace gui_states
    {
        class Game;
    }

    class ResourceContainer;
    class TextureAtlas;
    class Texture;
    class Animation;
    class Weapon;

    class Worm : public GameObject
    {
        friend collision_solvers::LandscapeWorm;

    public:
        static constexpr int        MAX_HEALTH          =  100;
        static constexpr int        SIZE                =    8;

        static constexpr int        ANIMATION_TIME      =   1000 / 10;

        static constexpr float      MOVEMENT_SPEED      =   10.0F / 1000.0F;
        static constexpr float      FLY_SPEED           =   120.0F / 1000.0F;

        static constexpr float      FALL_SPEED          =   60.0F / 1000.0F;
        static constexpr float      ROTATION_SPEED      =    2.5F / 1000.0F;

    private:
        enum States
        {
            MOVEMENT                =   0,
            IN_AIR                  =   1,
            STATE_COUNT
        };

        std::array<std::unique_ptr<Animation>, STATE_COUNT> animations;

        Weapon*             weapon = nullptr;
        
        float               x;
        float               y;

        float               fx = x;
        float               fy = y;
        
        float               nx          =   1.0F;
        float               ny          =   0.0F;

        float               rx;
        float               ry;

        States              currentState = MOVEMENT;
        WormTeams           team;

        int                 flyTime = 0;

        int                 health              =   MAX_HEALTH;
        
    public:
        static Worm create(ResourceContainer& resourceContainer, WormTeams team, float x, float y);

        Worm(decltype(animations) animations, WormTeams team, float x, float y);
        Worm(Worm&&) noexcept;
        ~Worm();

        Worm& operator=(Worm&&) noexcept;

        void update(unsigned delta) override;
        void render(Graphics& graphics, const Camera& camera) override;

        bool isKilled() const noexcept override {return health <= 0;}

        void takeDamage(int damage) noexcept {health -= damage;}
        void move(unsigned delta, bool side) noexcept;

        void setWeapon(Weapon* weapon) noexcept {this->weapon = weapon;}
        void useWeapon(gui_states::Game& game);

        void punch(float nx, float ny) noexcept;

        void rotate(unsigned delta, bool side) noexcept;

        auto getTeam() const noexcept {return team;}
        auto getX() const noexcept {return x;}
        auto getY() const noexcept {return y;}
        auto getNormX() const noexcept {return nx;}
        auto getNormY() const noexcept {return ny;}
        auto getHealth() const noexcept {return health;}
    };
}

#endif
