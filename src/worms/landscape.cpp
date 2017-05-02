#include "landscape.h"
#include "landscape_generator_adapter.h"
#include "landscape_generator.h"
#include "graphics.h"
#include "texture.h"
#include "surface.h"
#include "camera.h"

#include <utility>

using worms::Landscape;

Landscape Landscape::create(const VideoInfo& videoInfo)
{
    auto surface = Surface::create(videoInfo, WIDTH, WIDTH);
    surface.setColorKey(surface.makePixel(0xFF00FF));
    
    return Landscape{std::make_unique<Surface>(std::move(surface))};
}

Landscape::Landscape(std::unique_ptr<Surface> surface) :
    GameObject{LANDSCAPE}, surface{std::move(surface)}
{
}

Landscape::Landscape(Landscape&&) noexcept = default;

Landscape::~Landscape() = default;

Landscape& Landscape::operator=(Landscape&&) noexcept = default;

void Landscape::update(unsigned delta)
{
}

void Landscape::render(Graphics& graphics, const Camera& camera)
{
    if (rebuild)
    {
        texture = std::make_unique<Texture>(Texture::convert(graphics.getSdlRenderer(), surface->getHandle()));
        rebuild = false;
    }
    graphics.drawTexture(*texture, {static_cast<int>(-camera.x),
                                    static_cast<int>(-camera.y), WIDTH, WIDTH});
}

void Landscape::applyGeneration(const LandscapeGenerator& generator)
{
    generator.generate(LandscapeGeneratorAdapter{this});
}

void Landscape::destroy(int x0, int y0, int radius) noexcept
{
    const bool mustLock = SDL_MUSTLOCK(const_cast<SDL_Surface*>(surface->getHandle()));
    if (mustLock)
        ::SDL_LockSurface(const_cast<SDL_Surface*>(surface->getHandle()));

    surface->fillCircle(x0, y0, radius, surface->makePixel(0xFF00FF));
    
    if (mustLock)
        ::SDL_UnlockSurface(const_cast<SDL_Surface*>(surface->getHandle()));
    
    rebuild = true;
}

Uint32 Landscape::getPixel(int row, int col) const noexcept
{
    return surface->getRGB(surface->getPixel(row, col));
}

