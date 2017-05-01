#include "bullet.h"
#include "graphics.h"
#include "camera.h"
#include "particle.h"

#include <cmath>

using worms::Bullet;
using worms::Particle;

Bullet::Bullet(SDL_Rect                 area,
               const Texture*           texture,
               float                    x,
               float                    y,
               float                    nx,
               float                    ny,
               float                    movementSpeed,
               float                    fallSpeed,
               int                      size,
               int                      damage,
               int                      particlesPerSecond) noexcept : GameObject{BULLET},
    area   {area   },
    texture{texture},
    x      {x      },
    y      {y      }, 
    nx     {nx     },
    ny     {ny     },

    movementSpeed{movementSpeed},
    fallSpeed    {fallSpeed    },
    size         {size         }, 
    damage       {damage       },
    
    particlesPerSecond{particlesPerSecond}
{
}

// x(t) = x0 + v0 * t + 0.5g * t^2

void Bullet::update(unsigned delta)
{
    x = fx;
    y = fy;

    movementTime += delta;

    fx = x + nx * movementSpeed * movementTime * 1e-3F * delta;
    fy = y + ny * movementSpeed * movementTime * 1e-3F * delta + fallSpeed * movementTime * movementTime * 1e-6F * delta;

    accumParticleTime += delta;

    if (accumParticleTime >= 1000 / particlesPerSecond)
    {
        particleReady = true;
    }
}

void Bullet::render(Graphics& graphics, const Camera& camera)
{
    graphics.drawTexture(*texture,
            {static_cast<int>(x - camera.x), static_cast<int>(y - camera.y), size, size}, area,
                                    std::atan2(ny, nx) * 180.0 / M_PI + 90.0);
}

std::vector<std::unique_ptr<Particle>> Bullet::pickUpParticles()
{
    std::vector<std::unique_ptr<Particle>> particles;
    particleReady = false;
    
    const int count = accumParticleTime * particlesPerSecond / 1000;
    accumParticleTime = 0;

    for (int i = 0; i < count; ++i)
        particles.push_back(this->makeParticle());

    return particles;
}

