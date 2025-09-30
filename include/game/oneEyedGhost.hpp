#ifndef ONE_EYED_GHOST_HPP
#define ONE_EYED_GHOST_HPP

#include "engine/direction.hpp"
#include "engine/ncurses.hpp"
#include "engine/position.hpp"
#include "engine/window.hpp"
#include "game/board.hpp"
#include "game/ghost.hpp"
#include "game/player.hpp"
#include <optional>

class OneEyedGhost : public Ghost
{
  protected:
    // Returns the direction towards the player if theres no wall between ghost and player
    std::optional<Direction>
    getDirectionTowardsInSightPlayer(Position playerPosition,
                                     const Board& board);

  public:
    OneEyedGhost(Position position);

    void update(const Board& board, const Player& player) override;
    void render(Window* window) override;
    void render(Window* window, NCurses::ColorPair colorPair) override;
};

#endif
