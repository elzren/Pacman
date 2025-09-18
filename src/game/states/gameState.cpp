#include "game/states/gameState.hpp"
#include "engine/window.hpp"
#include "game/boardUtils.hpp"
#include "game/states/mainMenuState.hpp"
#include <memory>
#include <ncurses.h>

GameState::GameState()
{
    m_window = std::make_unique<Window>(0, 0, 0, 0);
    m_window->setTopLabel("Pacman");

    m_board.setBoard(BoardUtils::stringVectorToCharVector(BoardUtils::maze));
    m_player.setPosition({34, 16});

    int terminalWidth, terminalHeight;
    getmaxyx(stdscr, terminalHeight, terminalWidth);

    m_gameWindow = std::make_unique<Window>(
        m_window.get(), m_board.getWidth(), m_board.getHeight(),
        (terminalWidth - m_board.getWidth()) / 2,
        (terminalHeight - m_board.getHeight()) / 2);
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
    else
    {
        m_player.handleInput(input);
    }
}

void GameState::update([[maybe_unused]] StateManager& manager)
{
    m_player.update(m_board);
}

void GameState::render()
{
    if (m_window)
    {
        m_window->erase();

        m_board.render(m_gameWindow.get());
        m_player.render(m_gameWindow.get());

        m_window->refresh();
    }
}
