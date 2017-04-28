#include "particle.h"
#include "graphics.h"
#include "camera.h"

using worms::Particle;

Particle::Particle(float              x,
                   float              y,
                   float              nx,
                   float              ny,
                   float              movementSpeed,
                   float              fallSpeed,
                   Uint32             color) noexcept :
    GameObject{PARTICLE}, x{x}, y{y}, nx{nx}, ny{ny}, movementSpeed{movementSpeed}, fallSpeed{fallSpeed}, color{color}
{
}

void Particle::update(unsigned delta)
{
    x = fx;
    y = fy;

    fx = x + nx * movementSpeed * delta;
    fy = y + ny * movementSpeed * delta;

    ny += fallSpeed * delta;
    if (ny > 1.0F)
        ny = 1.0F;
}

void Particle::render(Graphics& graphics, const Camera& camera)
{
    graphics.setColor(color);
    graphics.drawPoint(x - camera.x, y - camera.y);
    graphics.setColor(0xFFFFFFFF);
}

