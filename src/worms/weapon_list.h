#ifndef WEAPONLIST_H
#define WEAPONLIST_H

#include "weapon.h"

#include <unordered_map>

namespace worms
{
    class TextureAtlas;

    class WeaponList
    {
    public:
        enum Types
        {
            BAZOOKA         =   0,
            GRENADE         =   1
        };

    private:
        std::unordered_map<Types, Weapon> weapons;

    public:
        explicit WeaponList(const TextureAtlas& textureAtlas);

        Weapon& findWeapon(Types type);
    };
}

#endif
