#include "window.h"

#include <stdexcept>

using worms::Window;

Window Window::create(const std::string& title, int w, int h, int x, int y, Uint32 flags)
{
    SDL_Window* const sdlWindow = ::SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (!sdlWindow)
        throw std::runtime_error{::SDL_GetError()};
    return Window{sdlWindow};
}

Window::Window(Window&& window) noexcept : handle{window.handle}
{
    window.handle = nullptr;
}

Window::~Window()
{
    ::SDL_DestroyWindow(handle);
}

Window& Window::operator=(Window&& window) noexcept
{
    if (this == &window) return *this;
    handle = window.handle;
    window.handle = nullptr;
    return *this;
}

Window::Size Window::requestSize() const noexcept
{
    int w, h;
    ::SDL_GetWindowSize(handle, &w, &h);
    return {w, h};
}

/*
worms::VideoInfo Window::requestVideoInfo() const noexcept
{
    Uint32 format, r, g, b, a;
    int bpp;
    ::SDL_PixelFormatEnumToMasks(format = ::SDL_GetWindowPixelFormat(handle), &bpp, &r, &g, &b, &a);
    return {format, r, g, b, a, bpp};
}
*/
