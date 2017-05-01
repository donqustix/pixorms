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

void LandscapeGeneratorAdapter::destroy(int x0, int y0, int radius) const noexcept
{
    landscape->destroy(x0, y0, radius);
}

