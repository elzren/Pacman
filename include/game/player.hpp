#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "engine/direction.hpp"
#include "engine/position.hpp"
#include "engine/window.hpp"
#include "game/board.hpp"
#include <optional>

class GhostManager;

class Player
{
  private:
    Position m_position{};
    Direction m_direction{};
    std::optional<Direction> m_inputDirection{std::nullopt};
    int m_lives{3};
    int m_dotsEaten{0};
    int m_score{0};

  public:
    Player() = default;

    void setPosition(Position position);
    void setDirection(const Direction& direction);

    Position getPosition() const;
    char getSymbol() const;
    Position getNextPosition(const Direction& direction) const;
    bool notFacingWall(const Direction& direction, const Board& board) const;
    int lives() const;
    int score() const;
    bool eatenAllDots(int totalDots) const;

    void eatDot(Board& board, GhostManager& ghostMgr);
    void kill();
    void incrementScore(int score);

    void handleInput(int input);
    void update(Board& board);
    void render(Window* window);
};

#endif
