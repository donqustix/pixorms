#ifndef BULLETFACTORY_H
#define BULLETFACTORY_H

#include <memory>

namespace worms
{
    class TextureAtlas;
    class Bullet;

    class BulletFactory
    {
        std::unique_ptr<TextureAtlas> textureAtlas;

    public:
        explicit BulletFactory(std::unique_ptr<TextureAtlas> textureAtlas);
        BulletFactory(BulletFactory&&) noexcept;
        ~BulletFactory();

        BulletFactory& operator=(BulletFactory&&) noexcept;

        std::unique_ptr<Bullet> makeBullet(float        x,
                                           float        y,
                                           float        nx,
                                           float        ny,
                                           int          weaponType) const;
    };
}

#endif
