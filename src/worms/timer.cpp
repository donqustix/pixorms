#include "timer.h"

#include <SDL2/SDL_timer.h>

using worms::Timer;

void Timer::initialize() noexcept
{
    previousTime = ::SDL_GetTicks();
}

Uint32 Timer::computeElapsedTime() noexcept
{
    const Uint32 currentTime = ::SDL_GetTicks();
    const Uint32 elapsedTime = currentTime - previousTime;
    previousTime = currentTime;
    return elapsedTime;
}

