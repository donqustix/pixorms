#include "application.h"
#include "gui_game_state_machine.h"
#include "graphics.h"
#include "resource_container.h"
#include "window.h"
#include "config.h"
#include "timer.h"
#include "resource_loader_list.h"
#include "gui_state.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <stdexcept>

using worms::Application;

struct Application::SDL
{
    SDL()
    {
        if (::SDL_Init(SDL_INIT_VIDEO) < 0)
            throw std::runtime_error{::SDL_GetError()};
    }

    ~SDL()
    {
        ::SDL_Quit();
    }
};

struct Application::SDLimage
{
    SDLimage()
    {
        if (!::IMG_Init(IMG_INIT_PNG))
            throw std::runtime_error{::IMG_GetError()};
    }

    ~SDLimage()
    {
        ::IMG_Quit();
    }
};

struct Application::SDLttf
{
    SDLttf()
    {
        if (::TTF_Init())
            throw std::runtime_error{::TTF_GetError()};
    }

    ~SDLttf()
    {
        ::TTF_Quit();
    }
};

Application::Application() : sdl     {std::make_unique<SDL     >()},
                             sdlImage{std::make_unique<SDLimage>()},
                             sdlTtf  {std::make_unique<SDLttf  >()}
{
    const auto config = Config::parseFile("res/configs/application.cfg");
    window = std::make_unique<Window>(Window::create("Worms", config.findValue<int>("w", "window"),
                                                              config.findValue<int>("h", "window")));
    ::SDL_SetWindowFullscreen(const_cast<SDL_Window*>(window->getHandle()), SDL_WINDOW_FULLSCREEN);

    graphics = std::make_unique<Graphics>(Graphics::create(*window, config.findValue<int>("virt_w", "graphics"),
                                                                    config.findValue<int>("virt_h", "graphics")));
    resourceContainer = std::make_unique<ResourceContainer>();

    ResourceLoaderList{}.load(*this, Config::parseFile("res/configs/resources.cfg"));

    guiGameStateMachine = std::make_unique<GuiGameStateMachine>(*this);
    spf = 1000 / config.findValue<unsigned>("max_fps");
}

Application::~Application() = default;

void Application::execute()
{
    SDL_Event sdlEvent;
    Timer timer;
    int lag = 0;

    timer.initialize();

    while (running)
    {
        const Uint32 elapsedTime = timer.computeElapsedTime();
        lag += elapsedTime;

        GuiState* const guiState = guiGameStateMachine->getCurrentState();

        while (::SDL_PollEvent(&sdlEvent))
        {
            if (sdlEvent.type == SDL_QUIT)
                running = false;
            if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                running = false;
            if (guiState)
                guiState->handle(sdlEvent);
        }

        while (lag >= spf)
        {
            if (guiState)
                guiState->update(spf);
            lag -= spf;
        }

        graphics->clear(0, 0, 0);
        if (guiState)
            guiState->render(*graphics);

        ::SDL_RenderPresent(const_cast<SDL_Renderer*>(graphics->getSdlRenderer()));
    }
}

