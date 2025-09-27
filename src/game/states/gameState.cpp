#include "game/states/gameState.hpp"
#include "engine/direction.hpp"
#include "engine/window.hpp"
#include "game/boardUtils.hpp"
#include "game/states/pauseState.hpp"
#include <memory>
#include <ncurses.h>
#include <string>

GameState::GameState()
{
    int terminalWidth, terminalHeight;
    getmaxyx(stdscr, terminalHeight, terminalWidth);

    m_window = std::make_unique<Window>(terminalWidth, terminalHeight, 0, 0);
    m_window->setTopLabel("Pacman");

    initializeBoard();
    initializePlayer();

    m_gameWindow = std::make_unique<Window>(
        m_window.get(), m_board.getWidth(), m_board.getHeight(),
        (terminalWidth - m_board.getWidth()) / 2,
        (terminalHeight - m_board.getHeight()) / 2);
}

GameState::~GameState() {}

void GameState::initializeBoard()
{
    m_board.setBoard(BoardUtils::stringVectorToCharVector(BoardUtils::maze));
    m_board.setPlayerInitialPosition({34, 16});
    m_board.setGhostInitialPosition({34, 9});
    m_board.setPlayerInitialDirection(Direction::LEFT);
}

void GameState::initializePlayer()
{
    m_player.setPosition(m_board.playerInitialPosition());
    m_player.setDirection(m_board.playerInitialDirection());
}

void GameState::restart()
{
    initializeBoard();
    initializePlayer();
    m_ghostManager.resetGhosts();
    ++m_level;
}

int GameState::frameDelay() const
{
    switch (m_level)
    {
    case 1:
        return 10;
    case 2:
        return 9;
    case 3:
        return 8;
    case 4:
        return 7;
    case 5:
        return 5;
    default:
        return 4;
    }
}

void GameState::incrementFrameCount()
{
    ++frameCount;
    if (frameCount >= 1000000)
    {
        frameCount = 0;
    }
}

void GameState::handleInput(StateManager& manager, int input)
{
    if (input == 27) // ESC key pressed
    {
        manager.pushState(std::make_unique<PauseState>());
    }

    m_player.handleInput(input);
}

void GameState::update([[maybe_unused]] StateManager& manager)
{
    if (m_player.lives() == 0)
    {
        manager.popState();
        manager.pushState(std::make_unique<PauseState>(false, "Game Over"));
        return;
    }

    if (m_player.eatenAllDots(m_board.dots()))
    {
        restart();
    }

    if (frameCount % frameDelay() == 0)
    {
        m_player.update(m_board);
        m_ghostManager.handleCollision(m_player, m_board);
    }

    if (frameCount % frameDelay() == 0)
    {
        m_ghostManager.update(m_board);
        m_ghostManager.handleCollision(m_player, m_board);
    }

    incrementFrameCount();
}

void GameState::render()
{
    if (m_window)
    {
        m_window->setBottomLabel(
            " " + std::string(m_player.lives(), '>') +
            " ]--[Level: " + std::to_string(m_level) +
            "]--[Score: " + std::to_string(m_player.score()));

        m_window->erase();

        m_board.render(m_gameWindow.get());
        m_player.render(m_gameWindow.get());
        m_ghostManager.render(m_gameWindow.get());

        m_window->refresh();
    }
}
