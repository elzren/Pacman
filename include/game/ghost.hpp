#ifndef GHOST_HPP
#define GHOST_HPP

#include "engine/direction.hpp"
#include "engine/position.hpp"
#include "game/board.hpp"
#include <set>

class Ghost
{
  private:
    Position m_position{0, 0};
    Direction m_direction{Direction::UP};

  public:
    Ghost() = default;
    Ghost(Position position);

    void setPosition(Position position);
    void setDirection(const Direction& direction);

    Position getPosition() const;

    Position getNextPosition(const Direction& direction) const;
    std::set<Direction> availableDirections(const Board& board) const;

    void update(const Board& board);
    void render(Window* window);
};

#endif
