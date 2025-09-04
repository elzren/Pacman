#include "game/states/mainMenuState.hpp"
#include "game/states/gameState.hpp"

MainMenuState::MainMenuState()
{
    m_window = std::make_unique<Window>(0, 0, 0, 0);
    m_window->setTopLabel("Pacman");
}

MainMenuState::~MainMenuState() {}

void MainMenuState::handleInput(StateManager& manager, int input)
{
    if (input == 'q')
        manager.popState();
    else if (input == '\n')
    {
        manager.pushState(std::make_unique<GameState>());
    }
}

void MainMenuState::update([[maybe_unused]] StateManager& manager) {}

void MainMenuState::render()
{
    if (m_window)
    {
        m_window->erase();
        m_window->addString(2, 1, "Main menu window");
        m_window->refresh();
    }
}
