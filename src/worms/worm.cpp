#include "worm.h"
#include "texture_atlas.h"
#include "graphics.h"
#include "camera.h"
#include "resource_container.h"
#include "animation.h"
#include "config.h"
#include "texture.h"
#include "weapon.h"

#include "gui_states/game.h"

#include <cmath>

using worms::Worm;

Worm Worm::create(ResourceContainer& resourceContainer, WormTeams team, float x, float y)
{
    auto animationMovement = Animation::load(Config::parseFile("res/textures/worm_movement.cfg"),
            *resourceContainer.find<Texture>("texture_worm_movement"));
    auto animationInAir    = Animation::load(Config::parseFile("res/textures/worm_in_air.cfg"),
            *resourceContainer.find<Texture>("texture_worm_in_air"));

    return {{{std::make_unique<Animation>(std::move(animationMovement)),
              std::make_unique<Animation>(std::move(animationInAir   ))}}, team, x, y};
}

Worm::Worm(decltype(animations) animations, WormTeams team, float x, float y) :
    GameObject{WORM}, animations{std::move(animations)}, x{x}, y{y}, team{team}
{
}

Worm::Worm(Worm&&) noexcept = default;

Worm::~Worm() = default;

Worm& Worm::operator=(Worm&&) noexcept = default;

void Worm::update(unsigned delta)
{
    if (health > MAX_HEALTH)
        health = MAX_HEALTH;
    else if (health < 0)
             health = 0;

    x = fx;
    y = fy;

    if (currentState == IN_AIR)
    {
        flyTime += delta;

        fx = x + nx * FLY_SPEED * flyTime * 1e-3F * delta;
        fy = y + ny * FLY_SPEED * flyTime * 1e-3F * delta + FALL_SPEED * flyTime * flyTime * 1e-6F * delta;

        rx = nx * FLY_SPEED * 1e-3F * delta;
        ry = ny * FLY_SPEED * 1e-3F * delta + FALL_SPEED * 1e-6F * delta * (2.0F * flyTime + 1.0F);

        animations[currentState]->update(delta, ANIMATION_TIME);
    }
    else
        fy = y + FALL_SPEED * delta;
}

void Worm::render(Graphics& graphics, const Camera& camera)
{
    if (currentState == IN_AIR)
        animations[currentState]->render(graphics, x - camera.x, y - camera.y, SIZE, SDL_FLIP_NONE,
                std::atan2(ry, rx) * 180.0 / M_PI + 45.0);
    else
    {
        animations[currentState]->render(graphics, x - camera.x, y - camera.y, SIZE, nx < 0.0F);
        if (weapon)
        {
            const int wx = x - camera.x + (SIZE - weapon->area.w) / 2;
            const int wy = y - camera.y + (SIZE - weapon->area.h) / 2;

            graphics.drawTexture(*weapon->texture, {wx, wy, weapon->area.w, weapon->area.h}, weapon->area,
                    std::atan2(ny, nx) * 180.0 / M_PI, nx < 0.0F ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);

            graphics.setColor(0xFF0000FF);
            graphics.drawPoint(x - camera.x + SIZE / 2 + 50 * nx, y - camera.y + SIZE / 2 + 50 * ny);
        }
    }

    graphics.setColor(0xFF0000AA);
    graphics.drawLine(x - camera.x, y - camera.y - 3, x - camera.x + SIZE, y - camera.y - 3);
    if (health)
    {
        graphics.setColor(0xFF00FF00);
        graphics.drawLine(x - camera.x, y - camera.y - 3, x - camera.x + health * SIZE / MAX_HEALTH, y - camera.y - 3);
    } 

    graphics.setColor(0xFFFFFFFF);
}

void Worm::move(unsigned delta, bool side) noexcept
{
    fx = x + MOVEMENT_SPEED * (2 * side - 1) * delta;
    nx = std::abs(nx)       * (2 * side - 1);
    animations[currentState]->update(delta, ANIMATION_TIME);
}

void Worm::useWeapon(gui_states::Game& game)
{
    game.addBullet(x, y, nx, ny, weapon->type);
    if (weapon->count != -1 && weapon->count)
      --weapon->count;
}

void Worm::punch(float nx, float ny) noexcept
{
    this->nx            =       nx;
    this->ny            =       ny;
    
    flyTime             =        0;
    
    currentState        =   IN_AIR;
}

void Worm::rotate(unsigned delta, bool side) noexcept
{
    if (nx < 0.0F)
        side = !side;

    const float px = (side ? -ny :  ny) * ROTATION_SPEED * delta;
    const float py = (side ?  nx : -nx) * ROTATION_SPEED * delta;

    nx += px;
    ny += py;

    const float invLength = 1.0F / std::sqrt(nx * nx + ny * ny);
    nx *= invLength;
    ny *= invLength;
}

