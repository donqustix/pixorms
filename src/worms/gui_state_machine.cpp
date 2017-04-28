#include "gui_state_machine.h"
#include "gui_state.h"

using worms::GuiStateMachine;

GuiStateMachine::GuiStateMachine() = default;

GuiStateMachine::GuiStateMachine(GuiStateMachine&&) noexcept = default;

GuiStateMachine::~GuiStateMachine() = default;

GuiStateMachine& GuiStateMachine::operator=(GuiStateMachine&&) noexcept = default;

