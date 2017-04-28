#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL_stdinc.h>

namespace worms
{
    class Timer
    {
        Uint32 previousTime;

    public:
        void initialize() noexcept;

        Uint32 computeElapsedTime() noexcept;
    };
}

#endif
