#include "gui_game_state_machine.h"
#include "state_types.h"

#include "gui_states/main_menu.h"
#include "gui_states/game.h"
#include "gui_states/game_preparation.h"

using worms::GuiGameStateMachine;

using worms::gui_states::MainMenu;
using worms::gui_states::Game;
using worms::gui_states::GamePreparation;

GuiGameStateMachine::GuiGameStateMachine(Application& application)
{
    this->addState<MainMenu       >(State::Types::MAIN_MENU       , application);
    this->addState<Game           >(State::Types::GAME            , application);
    this->addState<GamePreparation>(State::Types::GAME_PREPARATION, application);

    this->setCurrentState(State::Types::MAIN_MENU);
}

