#include "landscape.h"
#include "landscape_generator_adapter.h"
#include "landscape_generator.h"
#include "graphics.h"
#include "texture.h"
#include "surface.h"
#include "camera.h"

#include <algorithm>
#include <utility>

using worms::Landscape;

Landscape Landscape::create(const SDL_Renderer* sdlRenderer)
{
    auto surface = Surface::create(WIDTH, WIDTH, 32, SDL_PIXELFORMAT_RGBA32);

    auto texture = Texture::create(sdlRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, WIDTH, WIDTH);
    ::SDL_SetTextureBlendMode(const_cast<SDL_Texture*>(texture.getHandle()), SDL_BLENDMODE_BLEND);
    
    return Landscape{std::make_unique<Surface>(std::move(surface)),
                     std::make_unique<Texture>(std::move(texture))};
}

Landscape::Landscape(std::unique_ptr<Surface> surface,
                     std::unique_ptr<Texture> texture) :
    GameObject{LANDSCAPE}, surface{std::move(surface)}, texture{std::move(texture)}
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
    graphics.drawTexture(*texture, {static_cast<int>(-camera.x),
                                    static_cast<int>(-camera.y), WIDTH, WIDTH});
}

void Landscape::applyGeneration(const LandscapeGenerator& generator)
{
    generator.generate(LandscapeGeneratorAdapter{this});

    const bool mustLock = SDL_MUSTLOCK(const_cast<SDL_Surface*>(surface->getHandle()));
    if (mustLock)
        ::SDL_LockSurface(const_cast<SDL_Surface*>(surface->getHandle()));

    Uint32* pixels;
    int pitch;

    ::SDL_LockTexture(const_cast<SDL_Texture*>(texture->getHandle()), nullptr, reinterpret_cast<void**>(&pixels), &pitch);
    
    std::copy_n(static_cast<Uint32*>(surface->getHandle()->pixels), WIDTH * pitch / sizeof (Uint32), pixels);
    
    ::SDL_UnlockTexture(const_cast<SDL_Texture*>(texture->getHandle()));

    if (mustLock)
        ::SDL_UnlockSurface(const_cast<SDL_Surface*>(surface->getHandle()));
}

void Landscape::destroy(int x0, int y0, int radius) noexcept
{
    const bool mustLock = SDL_MUSTLOCK(const_cast<SDL_Surface*>(surface->getHandle()));
    if (mustLock)
        ::SDL_LockSurface(const_cast<SDL_Surface*>(surface->getHandle()));

    surface->fillCircle(x0, y0, radius, 0);
    
    const SDL_Rect rect{x0 - radius, y0 - radius, radius << 1, radius << 1};
    Uint32* pixels;
    int pitch;

    ::SDL_LockTexture(const_cast<SDL_Texture*>(texture->getHandle()), &rect, reinterpret_cast<void**>(&pixels), &pitch);
    
    const auto pixelsInRow = pitch / sizeof (Uint32);

    for (int i = 0; i < rect.h; ++i)
    {
        std::copy_n(static_cast<Uint32*>(surface->getHandle()->pixels) +
                (y0 - radius + i) * pixelsInRow + x0 - radius, rect.w, pixels + i * pixelsInRow);
    }
    
    ::SDL_UnlockTexture(const_cast<SDL_Texture*>(texture->getHandle()));

    if (mustLock)
        ::SDL_UnlockSurface(const_cast<SDL_Surface*>(surface->getHandle()));
}

Uint32 Landscape::getPixel(int row, int col) const noexcept
{
    return surface->getRGB(surface->getPixel(row, col));
}

