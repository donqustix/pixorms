#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "game_object.h"

#include <SDL2/SDL_render.h>

#include <utility>
#include <memory>

namespace worms
{
    class VideoInfo;
    class Texture;
    class Surface;

    class Landscape : public GameObject
    {
    public:
        static constexpr int WIDTH = 512;

    private:
        std::unique_ptr<Surface> surface;
        std::unique_ptr<Texture> texture;
        bool rebuild = true;

    public:
        static Landscape create(const VideoInfo&            videoInfo,
                                const Surface*              surface,
                                int                         scale           =   1);

        explicit Landscape(std::unique_ptr<Surface> surface);
        
        Landscape(Landscape&&) noexcept;
        ~Landscape();

        Landscape& operator=(Landscape&&) noexcept;

        void update(unsigned delta) override;
        void render(Graphics& graphics, const Camera& camera) override;

        void fillCircle(int x0, int y0, int radius, Uint32 color) noexcept;

        Uint32 getPixel(int row, int col) const noexcept;

        bool isKilled() const noexcept override {return false;}

        const auto& getSurface() const noexcept {return *surface;}
    };
}

#endif
