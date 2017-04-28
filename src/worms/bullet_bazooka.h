#ifndef BULLETBAZOOKA_H
#define BULLETBAZOOKA_H

#include "bullet.h"

namespace worms
{
    class TextureAtlas;

    class BulletBazooka : public Bullet
    {
    protected:
        std::unique_ptr<Particle> makeParticle() override;

    public:
        static BulletBazooka create(const TextureAtlas&     textureAtlas,
                                    float                   x,
                                    float                   y,
                                    float                   nx,
                                    float                   ny);

        BulletBazooka(SDL_Rect          area, 
                      const Texture*    texture,
                      float             x,
                      float             y,
                      float             nx,
                      float             ny) noexcept;
    };
}

#endif
