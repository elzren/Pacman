#ifndef GHOST_MANAGER_HPP
#define GHOST_MANAGER_HPP

#include "engine/window.hpp"
#include "game/ghost.hpp"
#include "game/player.hpp"
#include <vector>

class GhostManager
{
  private:
    std::vector<Ghost> m_ghosts{};
    size_t m_maxGhosts{4};
    int m_spawnTimeout{60};
    int m_frameCount{0};

  public:
    GhostManager();

    void handleCollision(Player& player, const Board& board);
    void spawnGhost(Position position);
    void resetGhosts();

    void update(const Board& board);
    void render(Window* window);
};

#endif
