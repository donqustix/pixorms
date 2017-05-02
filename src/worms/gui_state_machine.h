#ifndef GUISTATEMACHINE_H
#define GUISTATEMACHINE_H

#include <SDL2/SDL_events.h>

#include <unordered_map>
#include <stdexcept>
#include <utility>
#include <memory>

namespace worms
{
    struct GuiState;

    class Graphics;

    class GuiStateMachine
    {
        std::unordered_map<unsigned, std::unique_ptr<GuiState>> states;
        GuiState* currentState;

    public:
        GuiStateMachine();
        GuiStateMachine(GuiStateMachine&&) noexcept;
        ~GuiStateMachine();

        GuiStateMachine& operator=(GuiStateMachine&&) noexcept;

        template<typename T, typename... Args>
        void addState(unsigned id, Args&&... args)
        {
            if (states.find(id) != states.cend())
                throw std::runtime_error{"there is already a state with the id = " + std::to_string(id)};
            states.emplace(id, std::make_unique<T>(std::forward<Args>(args)...));
        }

        void setCurrentState(unsigned id)
        {
            const auto iter = states.find(id);
            if (iter == states.cend())
                throw std::runtime_error{"there is no a state with the id = " + std::to_string(id)};
            currentState = iter->second.get();
        }

        template<typename T>
        T* findState(unsigned id)
        {
            const auto iter = states.find(id);
            if (iter == states.cend())
                throw std::runtime_error{"there is no a state with the id = " + std::to_string(id)};
            return dynamic_cast<T*>(iter->second.get());
        }

        auto getCurrentState() noexcept {return currentState;}
    };
}

#endif
