#include "weapon_list.h"
#include "texture_atlas.h"

#include <stdexcept>
#include <string>

using worms::WeaponList;
using worms::Weapon;

WeaponList::WeaponList(const TextureAtlas& textureAtlas)
{
    weapons.insert({BAZOOKA, {textureAtlas.findArea("bazooka"), &textureAtlas.getTexture(), BAZOOKA, -1}});
    weapons.insert({GRENADE, {textureAtlas.findArea("grenade"), &textureAtlas.getTexture(), GRENADE, -1}});
}

Weapon& WeaponList::findWeapon(Types key)
{
    const auto iter = weapons.find(key);
    if (iter == weapons.cend())
        throw std::runtime_error{"there is no a weapon with the key" + std::to_string(key)};
    return iter->second;
}

