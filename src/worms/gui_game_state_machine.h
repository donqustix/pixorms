#ifndef GUIGAMESTATEMACHINE_H
#define GUIGAMESTATEMACHINE_H

#include "gui_state_machine.h"

namespace worms
{
    class Application;

    class GuiGameStateMachine : public GuiStateMachine
    {
    public:
        explicit GuiGameStateMachine(Application& application);
    };
}

#endif
