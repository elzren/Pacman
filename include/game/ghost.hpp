#ifndef GHOST_HPP
#define GHOST_HPP

#include "engine/direction.hpp"
#include "engine/ncurses.hpp"
#include "engine/position.hpp"
#include "game/board.hpp"
#include "game/player.hpp"
#include <set>

class Ghost
{
  protected:
    Position m_position{0, 0};
    Direction m_direction{Direction::UP};
    bool m_frightened{false};

  protected:
    Position getNextPosition(const Direction& direction) const;
    std::set<Direction> availableDirections(const Board& board) const;
    void move(const std::set<Direction>& availableDirections);
    // Erases direction only if there are more than one direction
    void eraseDirection(const Direction& direction,
                        std::set<Direction>& directions) const;

  public:
    Ghost(Position position);

    virtual ~Ghost() = default;

    void setPosition(Position position);
    void setDirection(const Direction& direction);
    void makeFrightened();
    void makeUnfrightened();

    Position getPosition() const;
    bool isFrightened() const;

    virtual void update(const Board& board, const Player& player);
    virtual void render(Window* window);
    virtual void render(Window* window, NCurses::ColorPair colorPair);
};

#endif
