#ifndef GHOST_MANAGER_HPP
#define GHOST_MANAGER_HPP

#include "engine/difficulty.hpp"
#include "engine/window.hpp"
#include "game/ghost.hpp"
#include "game/player.hpp"
#include <memory>
#include <vector>

class GhostManager
{
  private:
    std::vector<std::unique_ptr<Ghost>> m_ghosts{};
    size_t m_maxGhosts{4};
    Difficulty m_difficulty{};

    int m_spawnTimeout{40};
    int m_ghostMoves{0};

    bool m_frightenedMode{false};
    int m_frightenedTimer{0};
    int m_frightenedDuration{80};

  public:
    GhostManager(Difficulty difficulty);

    void handleCollision(Player& player, const Board& board);
    void spawnGhost(Position position);
    void resetGhosts();
    void incrementGhostMoves();
    void setFrightenedMode();
    void unsetFrightenedMode();

    void update(const Board& board, const Player& player);
    void render(Window* window);
};

#endif
