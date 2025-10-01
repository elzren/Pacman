#include "game/ghostManager.hpp"
#include "engine/difficulty.hpp"
#include "engine/ncurses.hpp"
#include "engine/window.hpp"
#include "game/chaserGhost.hpp"
#include "game/ghost.hpp"
#include "game/oneEyedGhost.hpp"
#include "game/player.hpp"
#include <memory>

GhostManager::GhostManager(Difficulty difficulty) : m_difficulty{difficulty}
{
    m_ghosts.reserve(m_maxGhosts);

    m_spawnTimeout = m_difficulty == Difficulty::HARD     ? 20
                     : m_difficulty == Difficulty::MEDIUM ? 30
                                                          : m_spawnTimeout;
}

void GhostManager::handleCollision(Player& player, const Board& board)
{
    for (auto& ghost : m_ghosts)
    {
        if (ghost->getPosition() == player.getPosition())
        {
            if (ghost->isFrightened())
            {
                ghost->setPosition(board.ghostInitialPosition());
                ghost->makeUnfrightened();
                player.incrementScore(100);
            }
            else
            {
                player.kill();
                if (player.lives())
                {
                    player.setPosition(board.playerInitialPosition());
                    player.setDirection(board.playerInitialDirection());
                    resetGhosts();
                }
            }
        }
    }
}

void GhostManager::spawnGhost(Position position)
{
    if (m_ghosts.size() < m_maxGhosts && m_ghostMoves % m_spawnTimeout == 0)
    {
        switch (m_difficulty)
        {
        case Difficulty::EASY:
            if (m_ghosts.size() == m_maxGhosts - 1) // last one
            {
                m_ghosts.emplace_back(std::make_unique<ChaserGhost>(position));
            }
            else if (m_ghosts.size() == m_maxGhosts - 2) // second last one
            {
                m_ghosts.emplace_back(std::make_unique<OneEyedGhost>(position));
            }
            else
            {
                m_ghosts.emplace_back(std::make_unique<Ghost>(position));
            }
            break;
        case Difficulty::MEDIUM:
            if (m_ghosts.size() == m_maxGhosts - 1)
            {
                m_ghosts.emplace_back(std::make_unique<ChaserGhost>(position));
            }
            else if (m_ghosts.size() == m_maxGhosts - 2 ||
                     m_ghosts.size() == m_maxGhosts - 3)
            {
                m_ghosts.emplace_back(std::make_unique<OneEyedGhost>(position));
            }
            else
            {
                m_ghosts.emplace_back(std::make_unique<Ghost>(position));
            }
            break;
        case Difficulty::HARD:
            if (m_ghosts.size() == m_maxGhosts - 1 ||
                m_ghosts.size() == m_maxGhosts - 2)
            {
                m_ghosts.emplace_back(std::make_unique<ChaserGhost>(position));
            }
            else
            {
                m_ghosts.emplace_back(std::make_unique<OneEyedGhost>(position));
            }
            break;
        }
    }
}

void GhostManager::resetGhosts()
{
    m_ghosts.clear();
    m_ghostMoves = 0;
}

void GhostManager::incrementGhostMoves()
{
    ++m_ghostMoves;
    if (m_ghostMoves >= 1000000)
    {
        m_ghostMoves = 0;
    }
}

void GhostManager::setFrightenedMode()
{
    m_frightenedMode = true;
    m_frightenedTimer = 0;

    for (auto& ghost : m_ghosts)
    {
        ghost->makeFrightened();
    }
}

void GhostManager::unsetFrightenedMode()
{
    m_frightenedMode = false;

    for (auto& ghost : m_ghosts)
    {
        ghost->makeUnfrightened();
    }
}

void GhostManager::update(const Board& board, const Player& player)
{
    spawnGhost(board.ghostInitialPosition());

    for (auto& ghost : m_ghosts)
    {
        // if frightened, slow down the ghost
        if (!ghost->isFrightened() || m_frightenedTimer % 3 != 0)
        {
            ghost->update(board, player);
        }
    }

    incrementGhostMoves();

    if (m_frightenedMode)
    {
        ++m_frightenedTimer;

        if (m_frightenedTimer >= m_frightenedDuration)
        {
            unsetFrightenedMode();
        }
    }
}

void GhostManager::render(Window* window)
{
    if (window)
    {
        for (auto& ghost : m_ghosts)
        {
            if (ghost->isFrightened())
            {
                if (m_frightenedTimer > m_frightenedDuration - 10 &&
                    m_frightenedTimer % 2 == 0)
                {
                    ghost->render(window);
                }
                else
                {
                    ghost->render(window, NCurses::BLUE_DEFAULT);
                }
            }
            else
            {
                ghost->render(window);
            }
        }

        if (m_ghostMoves % 8 > 3)
        {
            window->addChar(34, 10, 'O', NCurses::RED_DEFAULT);
        }
        else
        {
            window->addChar(34, 10, 'o', NCurses::WHITE_DEFAULT);
        }
    }
}
