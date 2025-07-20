#include "engine/ncurses.hpp"
#include "engine/stateManager.hpp"
#include "game/states/mainMenuState.hpp"

int main()
{
    NCurses ncurses{};
    StateManager stateManager{};

    stateManager.pushState(std::make_unique<MainMenuState>());
    stateManager.run();

    return 0;
}
