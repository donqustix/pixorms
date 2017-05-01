#ifndef PARTICLE_H
#define PARTICLE_H

#include "game_object.h"

#include <SDL2/SDL_stdinc.h>

namespace worms
{
    namespace collision_solvers
    {
        struct LandscapeParticle;
    }

    class Particle : public GameObject
    {
        friend collision_solvers::LandscapeParticle;

        float               x;
        float               y;

        float               fx = x;
        float               fy = y;

        float               nx;
        float               ny;

        float               movementSpeed;
        float               fallSpeed;

        Uint32              color;

        int                 movementTime = 0;

        bool                killed = false;

    public:
        Particle(float              x,
                 float              y,
                 float              nx,
                 float              ny,
                 float              movementSpeed,
                 float              fallSpeed,
                 Uint32             color) noexcept;

        void update(unsigned delta) override;
        void render(Graphics& graphics, const Camera& camera) override;
        
        void kill() noexcept {killed = true;}
        bool isKilled() const noexcept override {return killed;}

        auto getX() const noexcept {return x;}
        auto getY() const noexcept {return y;}
        auto getNormX() const noexcept {return nx;}
        auto getNormY() const noexcept {return ny;}
        auto getColor() const noexcept {return color;}
    };
}

#endif
