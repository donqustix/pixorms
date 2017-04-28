#include "main_menu.h"
#include "game.h"

#include "worms/gui_button.h"
#include "worms/gui_game_state_machine.h"
#include "worms/graphics.h"
#include "worms/application.h"
#include "worms/state_types.h"
#include "worms/button_factory.h"
#include "worms/state_types.h"
#include "worms/player_brain.h"
#include "worms/worm.h"
#include "worms/weapon_list.h"
#include "worms/texture_atlas.h"
#include "worms/config.h"
#include "worms/resource_container.h"

using worms::gui_states::MainMenu;

MainMenu::MainMenu(Application& application)
{
    const ButtonFactory buttonFactory{application};

    const SDL_Rect& buttonInfo = buttonFactory.getButtonInfo();

    const int startX = buttonInfo.x - buttonInfo.w;
    const int startY = buttonInfo.y - buttonInfo.h - 20;

    const int buttonWidth  = buttonInfo.w << 1;
    const int buttonHeight = buttonInfo.h << 1;

    buttons.push_back(buttonFactory.makeButton("start game", startX, startY, buttonWidth, buttonHeight,
                [&application] {
        const auto guiGameState = application.getGuiGameStateMachine().findState<Game>(State::GAME);

        Game::PlayerData playerData;
        playerData.player = std::make_unique<PlayerBrain>();
        playerData.worms.push_back(std::make_unique<Worm>(
                    Worm::create(application.getResourceContainer(), WormTeams::RED, 100, 100)));
        playerData.weaponList = std::make_unique<WeaponList>(
                TextureAtlas::load(Config::parseFile("res/textures/weapons.cfg"),
                    *application.getResourceContainer().find<Texture>("texture_weapons")));
        guiGameState->addPlayerData(std::move(playerData), static_cast<int>(WormTeams::RED));

        application.getGuiGameStateMachine().setCurrentState(State::GAME);
    }));

    buttons.push_back(buttonFactory.makeButton("exit", startX, startY + buttonHeight + 10, buttonWidth, buttonHeight,
                [&application] {
        application.stopRunning();
    }));
}

MainMenu::MainMenu(MainMenu&&) noexcept = default;

MainMenu::~MainMenu() = default;

MainMenu& MainMenu::operator=(MainMenu&&) noexcept = default;

void MainMenu::update(unsigned delta)
{
}

void MainMenu::render(Graphics& graphics)
{
    for (const auto& b : buttons)
        b->render(graphics);
}

void MainMenu::handle(const SDL_Event& sdlEvent)
{
    for (const auto& b : buttons)
        b->handle(sdlEvent);
}

