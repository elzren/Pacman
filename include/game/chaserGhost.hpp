#ifndef CHASER_GHOST_HPP
#define CHASER_GHOST_HPP

#include "engine/ncurses.hpp"
#include "engine/position.hpp"
#include "engine/window.hpp"
#include "game/board.hpp"
#include "game/ghost.hpp"
#include "game/player.hpp"
#include <set>

class ChaserGhost : public Ghost
{
  protected:
    // Erases directions that are not towards the current player position
    void eraseDirectionsAwayFromPlayer(std::set<Direction>& directions,
                                       Position playerPosition);

  public:
    ChaserGhost(Position position);

    void update(const Board& board, const Player& player) override;
    void render(Window* window) override;
    void render(Window* window, NCurses::ColorPair colorPair) override;
};

#endif
