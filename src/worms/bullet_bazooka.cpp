#include "bullet_bazooka.h"
#include "texture_atlas.h"
#include "particle.h"

#include <cstdlib>
#include <cmath>

using worms::BulletBazooka;
using worms::Particle;

BulletBazooka BulletBazooka::create(const TextureAtlas&     textureAtlas,
                                    float                   x,
                                    float                   y,
                                    float                   nx,
                                    float                   ny)
{
    return {textureAtlas.findArea("bazooka"), &textureAtlas.getTexture(), x, y, nx, ny};
}

BulletBazooka::BulletBazooka(SDL_Rect           area,
                             const Texture*     texture,
                             float              x,
                             float              y,
                             float              nx,
                             float              ny) noexcept :
    Bullet{area, texture, x, y, nx, ny, 80.0F / 1000.0F, 30.0F / 1000.0F, 2, 40, 45}
{
}

std::unique_ptr<Particle> BulletBazooka::makeParticle()
{
    const float x = this->getX() + this->getSize() / 2;
    const float y = this->getY() + this->getSize() / 2;
    
    float nx = -this->getNormX() + (-60 + std::rand() % 121) * 0.01F;
    float ny = -this->getNormY() + (-60 + std::rand() % 121) * 0.01F;

    const auto invLength = 1.0F / std::sqrt(nx * nx + ny * ny);
    nx *= invLength;
    ny *= invLength;

    return std::make_unique<Particle>(
                Particle{x, y, nx, ny, 30.0F / 1000.0F, 10.0F / 1000.0F, 0xFFAAAAAA});
}

