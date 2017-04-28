#include "landscape.h"
#include "graphics.h"
#include "texture.h"
#include "surface.h"
#include "camera.h"
#include "video_info.h"
#include "bullet.h"
#include "particle.h"

using worms::Landscape;

Landscape Landscape::create(const VideoInfo&            videoInfo,
                            const Surface*              surface,
                            int                         scale)
{
    auto landscapeSurface = Surface::create(videoInfo, WIDTH, WIDTH);
    landscapeSurface.setColorKey(landscapeSurface.makePixel(0xFF00FF));
    
    const int w = surface->getHandle()->w * scale;
    const int h = surface->getHandle()->h * scale;

    for (int i = 0; i < WIDTH; i += h)
    {
        for (int j = 0; j < WIDTH; j += w)
        {
            SDL_Rect dstrect{j, i, w, h};
            ::SDL_BlitScaled(const_cast<SDL_Surface*>(surface        ->getHandle()), nullptr,
                             const_cast<SDL_Surface*>(landscapeSurface.getHandle()), &dstrect);
        }
    }

    return Landscape{std::make_unique<Surface>(std::move(landscapeSurface))};
}

Landscape::Landscape(std::unique_ptr<Surface> surface) :
    GameObject{LANDSCAPE}, surface{std::move(surface)}
{
    fillCircle(100, 100, 100, this->surface->makePixel(0xFF00FF));

    for (int i = 0; i < 8; ++i)
    {
        fillCircle(100 + (i + 1) * 50, 100 + i * 5 * i, 100,
                this->surface->makePixel(0xFF00FF));
    }
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

void Landscape::fillCircle(int x0, int y0, int radius, Uint32 color) noexcept
{
    auto drawLine = [this, color](int x1, int x2, int y) {
        if (y < 0 || y >= surface->getHandle()->h)
            return;
        for (int i = x1; i < x2; ++i)
        {
            if (i < 0 || i >= surface->getHandle()->w)
                continue;
            surface->setPixel(y, i, color);
        }
    };

    const bool mustLock = SDL_MUSTLOCK(const_cast<SDL_Surface*>(surface->getHandle()));
    if (mustLock)
        ::SDL_LockSurface(const_cast<SDL_Surface*>(surface->getHandle()));

    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        drawLine(x0 - x, x0 + x, y0 + y);
        drawLine(x0 - y, x0 + y, y0 + x);
        drawLine(x0 - y, x0 + y, y0 - x);
        drawLine(x0 - x, x0 + x, y0 - y);

        if (err <= 0)
        {
            ++y;
            err += 2 * y + 1;
        }
        if (err > 0)
        {
            --x;
            err -= 2 * x + 1;
        }
    }

    if (mustLock)
        ::SDL_UnlockSurface(const_cast<SDL_Surface*>(surface->getHandle()));

    rebuild = true;
}

Uint32 Landscape::getPixel(int row, int col) const noexcept
{
    return surface->getRGB(surface->getPixel(row, col));
}

