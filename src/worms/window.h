#ifndef WINDOW_H
#define WINDOW_H

//#include "video_info.h"

#include <SDL2/SDL_video.h>

#include <string>

namespace worms
{
    class Window
    {
    public:
        struct Size
        {
            int w;
            int h;
        };

    private:
        SDL_Window* handle;

    public:
        static Window create(const std::string& title,
                             int w,
                             int h,
                             int x           =      SDL_WINDOWPOS_CENTERED,
                             int y           =      SDL_WINDOWPOS_CENTERED,
                             Uint32 flags    =      SDL_WINDOW_SHOWN      );

        explicit Window(SDL_Window* sdlWindow) noexcept : handle{sdlWindow} {}
        Window(Window&& window) noexcept;
        ~Window();

        Window& operator=(Window&& window) noexcept;

        //VideoInfo requestVideoInfo() const noexcept;
        Size requestSize() const noexcept;

        const auto* getHandle() const noexcept {return handle;}
    };
}

#endif
