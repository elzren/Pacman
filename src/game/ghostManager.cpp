#include "game/ghostManager.hpp"
#include "engine/ncurses.hpp"
#include "engine/window.hpp"

GhostManager::GhostManager() { m_ghosts.reserve(m_maxGhosts); }

void GhostManager::handleCollision(Player& player, const Board& board)
{
    for (const auto& ghost : m_ghosts)
    {
        if (ghost.getPosition() == player.getPosition())
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

void GhostManager::spawnGhost(Position position)
{
    if (m_ghosts.size() < m_maxGhosts && m_ghostMoves % m_spawnTimeout == 0)
    {
        m_ghosts.emplace_back(position);
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

void GhostManager::update(const Board& board)
{
    spawnGhost(board.ghostInitialPosition());

    for (auto& ghost : m_ghosts)
    {
        ghost.update(board);
    }

    incrementGhostMoves();
}

void GhostManager::render(Window* window)
{
    if (window)
    {
        for (auto& ghost : m_ghosts)
        {
            ghost.render(window);
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
