#include "game/states/mainMenuState.hpp"
#include "game/states/gameState.hpp"

MainMenuState::MainMenuState()
{
    m_window = newwin(10, 20, 0, 0);
}

MainMenuState::~MainMenuState()
{
    delwin(m_window);
}

void MainMenuState::handleInput(StateManager& manager, int input)
{
    if(input == 'q')
        manager.popState();
    else if (input == '\n')
    {
        manager.pushState(std::make_unique<GameState>());
    }
}

void MainMenuState::update([[maybe_unused]] StateManager& manager)
{

}

void MainMenuState::render()
{
    werase(m_window);
    mvwaddstr(m_window, 1, 1, "Main menu window");
    wrefresh(m_window);
}
