#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "engine/position.hpp"
#include "engine/window.hpp"
#include "game/board.hpp"
#include <optional>

class Player
{
  public:
    enum Direction
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

  private:
    Position m_position{0, 0};
    Direction m_direction{LEFT};
    std::optional<Direction> m_inputDirection{std::nullopt};

  public:
    Player() = default;

    void setPosition(Position position);
    void setDirection(Direction direction);

    char getSymbol() const;
    Position getNextPosition(Direction direction) const;
    bool notFacingWall(Direction direction, const Board& board) const;

    void eatItem(Board& board);

    void handleInput(int input);
    void update(Board& board);
    void render(Window* window);
};

#endif
