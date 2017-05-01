#ifndef LANDSCAPEGENERATORADAPTER_H
#define LANDSCAPEGENERATORADAPTER_H

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
        void destroy(int x0, int y0, int radius) const noexcept;
    };
}

#endif
