#ifndef BULLET_H
#define BULLET_H

#include "game_object.h"

#include <SDL2/SDL_rect.h>

#include <vector>
#include <memory>

namespace worms
{
    namespace collision_solvers
    {
        class LandscapeBullet;
    }

    class Particle;
    class Texture;

    class Bullet : public GameObject
    {
        friend collision_solvers::LandscapeBullet;

        SDL_Rect            area;

        const Texture*      texture;

        float               x;
        float               y;

        float               fx = x;
        float               fy = y;
        
        float               nx;
        float               ny;

        float               movementSpeed;
        float               fallSpeed;

        int                 size;
        int                 damage;

        int                 particlesPerSecond;
        int                 accumParticleTime = 0;
        
        bool                killed = false;
        bool                particleReady = false;

    protected:
        virtual std::unique_ptr<Particle> makeParticle() = 0;

    public:
        Bullet(SDL_Rect                 area,
               const Texture*           texture,
               float                    x,
               float                    y,
               float                    nx,
               float                    ny,
               float                    movementSpeed,
               float                    fallSpeed,
               int                      size,
               int                      damage,
               int                      particlesPerSecond) noexcept;

        void update(unsigned delta) override;
        void render(Graphics& graphics, const Camera& camera) override;

        void kill() noexcept {killed = true;}
        bool isKilled() const noexcept override {return killed;}

        std::vector<std::unique_ptr<Particle>> pickUpParticles();
        
        auto isParticleReady() const noexcept {return particleReady;}

        auto getX() const noexcept {return x;}
        auto getY() const noexcept {return y;}
        auto getNormX() const noexcept {return nx;}
        auto getNormY() const noexcept {return ny;}
        auto getSize() const noexcept {return size;}
        auto getDamage() const noexcept {return damage;}
    };
}

#endif
