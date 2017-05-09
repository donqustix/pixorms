#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "game_object.h"

#include <SDL2/SDL_render.h>

#include <memory>

namespace worms
{
    struct LandscapeGenerator;

    class Texture;
    class Surface;

    class Landscape : public GameObject
    {
        friend class LandscapeGeneratorAdapter;

    public:
        static constexpr int WIDTH = 512;

    private:
        std::unique_ptr<Surface> surface;
        std::unique_ptr<Texture> texture;

    public:
        static Landscape create(const SDL_Renderer* sdlRenderer);

        explicit Landscape(std::unique_ptr<Surface> surface,
                           std::unique_ptr<Texture> texture);
        
        Landscape(Landscape&&) noexcept;
        ~Landscape();

        Landscape& operator=(Landscape&&) noexcept;

        void update(unsigned delta) override;
        void render(Graphics& graphics, const Camera& camera) override;

        bool isKilled() const noexcept override {return false;}

        void applyGeneration(const LandscapeGenerator& generator);

        void destroy(int x0, int y0, int radius) noexcept;

        Uint32 getPixel(int row, int col) const noexcept;

        const auto& getSurface() const noexcept {return *surface;}
    };
}

#endif
