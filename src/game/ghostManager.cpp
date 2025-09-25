#include "game/ghostManager.hpp"
#include "engine/ncurses.hpp"
#include "engine/window.hpp"

GhostManager::GhostManager() { m_ghosts.reserve(m_maxGhosts); }

void GhostManager::handleCollision(Player& player)
{
    for (const auto& ghost : m_ghosts)
    {
        if (ghost.getPosition() == player.getPosition())
            player.kill();
    }
}

void GhostManager::spawnGhost(Position position)
{
    if (m_ghosts.size() < m_maxGhosts && m_frameCount % m_spawnTimeout == 0)
    {
        m_ghosts.emplace_back(position);
    }
}

void GhostManager::update(const Board& board)
{
    spawnGhost(board.ghostInitialPosition());

    for (auto& ghost : m_ghosts)
    {
        ghost.update(board);
    }

    ++m_frameCount;
}

void GhostManager::render(Window* window)
{
    if (window)
    {
        for (auto& ghost : m_ghosts)
        {
            ghost.render(window);
        }

        if (m_frameCount % 8 > 3)
        {
            window->addChar(34, 10, 'O', NCurses::RED_DEFAULT);
        }
        else
        {
            window->addChar(34, 10, 'o', NCurses::WHITE_DEFAULT);
        }
    }
}
