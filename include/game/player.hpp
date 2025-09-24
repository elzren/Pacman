#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "engine/direction.hpp"
#include "engine/position.hpp"
#include "engine/window.hpp"
#include "game/board.hpp"
#include <optional>

class Player
{
  private:
    Position m_position{0, 0};
    Direction m_direction{Direction::LEFT};
    std::optional<Direction> m_inputDirection{std::nullopt};
    bool alive{true};

  public:
    Player() = default;

    void setPosition(Position position);
    void setDirection(const Direction& direction);

    Position getPosition() const;
    char getSymbol() const;
    Position getNextPosition(const Direction& direction) const;
    bool notFacingWall(const Direction& direction, const Board& board) const;
    bool isDead() const;

    void eatItem(Board& board);
    void kill();

    void handleInput(int input);
    void update(Board& board);
    void render(Window* window);
};

#endif
