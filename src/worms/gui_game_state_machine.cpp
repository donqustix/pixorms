#include "gui_game_state_machine.h"
#include "state_types.h"

#include "gui_states/main_menu.h"
#include "gui_states/game.h"

using worms::GuiGameStateMachine;

using worms::gui_states::MainMenu;
using worms::gui_states::Game;

GuiGameStateMachine::GuiGameStateMachine(Application& application)
{
    this->addState<MainMenu>(State::Types::MAIN_MENU, application);
    this->addState<Game    >(State::Types::GAME     , application);

    this->setCurrentState(State::Types::MAIN_MENU);
}

