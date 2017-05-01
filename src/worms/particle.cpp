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

// x(t) = x0 + v0 * t + 0.5g * t^2

void Particle::update(unsigned delta)
{
    x = fx;
    y = fy;

    movementTime += delta;

    fx = x + nx * movementSpeed * movementTime * 1e-3F * delta;
    fy = y + ny * movementSpeed * movementTime * 1e-3F * delta + fallSpeed * movementTime * movementTime * 1e-6F * delta;
}

void Particle::render(Graphics& graphics, const Camera& camera)
{
    graphics.setColor(color);
    graphics.drawPoint(x - camera.x, y - camera.y);
    graphics.setColor(0xFFFFFFFF);
}

