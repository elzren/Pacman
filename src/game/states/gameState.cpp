#include "game/states/gameState.hpp"
#include "game/states/mainMenuState.hpp"

GameState::GameState()
{
    m_window = std::make_unique<Window>(0, 0, 0, 0);
    m_window->setTopLabel("Pacman");
}

GameState::~GameState() {}

void GameState::handleInput(StateManager& manager, int input)
{
    if (input == 'q')
    {
        manager.popState();
    }
    else if (input == 27) // ESC key pressed
    {
        manager.popState();
        manager.pushState(std::make_unique<MainMenuState>());
    }
}

void GameState::update([[maybe_unused]] StateManager& manager) {}

void GameState::render()
{
    if (m_window)
    {
        m_window->erase();
        m_window->addString(2, 1, "Game window");
        m_window->refresh();
    }
}
