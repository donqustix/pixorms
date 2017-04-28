#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

namespace worms
{
    class Window;
    class Graphics;
    class ResourceContainer;
    class GuiGameStateMachine;

    class Application
    {
        struct SDL;
        std::unique_ptr<SDL>        sdl;

        struct SDLimage;
        std::unique_ptr<SDLimage>   sdlImage;

        struct SDLttf;
        std::unique_ptr<SDLttf>     sdlTtf;

        std::unique_ptr<Window>                     window;
        std::unique_ptr<Graphics>                   graphics;
        std::unique_ptr<ResourceContainer>          resourceContainer;
        std::unique_ptr<GuiGameStateMachine>        guiGameStateMachine;
        
        int spf;
        bool running = true;

    public:
        Application();
        Application(const Application&) = delete;
        ~Application();

        Application& operator=(const Application&) = delete;

        void execute();
        void stopRunning() noexcept {running = false;}

        auto& getWindow() noexcept {return *window;}
        auto& getGraphics() noexcept {return *graphics;}
        auto& getResourceContainer() noexcept {return *resourceContainer;}
        auto& getGuiGameStateMachine() noexcept {return *guiGameStateMachine;}
    };
}

#endif
