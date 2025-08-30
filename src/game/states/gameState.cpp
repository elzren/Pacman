#include "game/states/gameState.hpp"

GameState::GameState() { m_window = newwin(10, 20, 0, 0); }

GameState::~GameState() { delwin(m_window); }

void GameState::handleInput(StateManager& manager, int input)
{
    if (input == 'q')
    {
        manager.popState();
        manager.popState();
    }
    else if (input == 27) // ESC key pressed
        manager.popState();
}

void GameState::update([[maybe_unused]] StateManager& manager) {}

void GameState::render()
{
    werase(m_window);
    mvwaddstr(m_window, 1, 1, "Game window");
    wrefresh(m_window);
}
