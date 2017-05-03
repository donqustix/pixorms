#include "landscape_generator_adapter.h"
#include "landscape.h"
#include "surface.h"

using worms::LandscapeGeneratorAdapter;

void LandscapeGeneratorAdapter::drawSurface(const Surface& surface, int x, int y, int w, int h) const noexcept
{
    SDL_Rect dstrect{x, y, w, h};
    ::SDL_BlitScaled(const_cast<SDL_Surface*>(           surface .getHandle()), nullptr,
                     const_cast<SDL_Surface*>(landscape->surface->getHandle()), &dstrect);
}

void LandscapeGeneratorAdapter::fillCircle(int x0, int y0, int radius, Uint32 color) const noexcept
{
    landscape->surface->fillCircle(x0, y0, radius, color);
}

void LandscapeGeneratorAdapter::setPixel(int row, int col, Uint32 pixel) const noexcept
{
    landscape->surface->setPixel(row, col, pixel);
}

