#ifndef LANDSCAPEGENERATORADAPTER_H
#define LANDSCAPEGENERATORADAPTER_H

#include <SDL2/SDL_stdinc.h>

namespace worms
{
    class Landscape;
    class Surface;

    class LandscapeGeneratorAdapter
    {
        Landscape* landscape;

    public:
        explicit LandscapeGeneratorAdapter(Landscape* landscape) noexcept : landscape{landscape} {}

        void drawSurface(const Surface& surface, int x, int y, int w, int h) const noexcept;
        void fillCircle(int x0, int y0, int radius, Uint32 color) const noexcept;

        void setPixel(int row, int col, Uint32 pixel) const noexcept;

        const Landscape& getLandscape() const noexcept {return *landscape;}
    };
}

#endif
