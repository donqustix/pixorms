#include "bullet_factory.h"
#include "bullet_bazooka.h"
#include "weapon_list.h"
#include "texture_atlas.h"

#include <stdexcept>

using worms::BulletFactory;
using worms::Bullet;

BulletFactory::BulletFactory(std::unique_ptr<TextureAtlas> textureAtlas) :
    textureAtlas{std::move(textureAtlas)}
{
}

BulletFactory::BulletFactory(BulletFactory&&) noexcept = default;

BulletFactory::~BulletFactory() = default;

BulletFactory& BulletFactory::operator=(BulletFactory&&) noexcept = default;

std::unique_ptr<Bullet> BulletFactory::makeBullet(float         x,
                                                  float         y,
                                                  float         nx,
                                                  float         ny,
                                                  int           weaponType) const
{
    switch (weaponType)
    {
        case WeaponList::BAZOOKA:
            return std::make_unique<BulletBazooka>(BulletBazooka::create(*textureAtlas, x, y, nx, ny));
        case WeaponList::GRENADE:
            break;
    }

    throw std::runtime_error{"an unknow weapon type"};
}

