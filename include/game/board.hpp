#ifndef BOARD_HPP
#define BOARD_HPP

#include "engine/direction.hpp"
#include "engine/position.hpp"
#include "engine/window.hpp"
#include <vector>

class Board
{
  private:
    std::vector<std::vector<char>> m_board{};
    int m_height{};
    int m_width{};
    int m_dots{};
    Position m_playerInitialPosition{};
    Position m_ghostInitialPosition{};
    Direction m_playerInitialDirection{};

  public:
    Board() = default;

    void setBoard(const std::vector<std::vector<char>>& board);

    int getHeight() const;
    int getWidth() const;

    char getTile(Position position) const;
    void setTile(Position position, char ch);

    bool isSmallDot(char ch) const;
    bool isSmallDot(Position position) const;

    bool isBigDot(char ch) const;
    bool isBigDot(Position position) const;

    bool isDot(char ch) const;
    bool isDot(Position position) const;

    bool isVisibleWall(char ch) const;
    bool isInvisibleWall(char ch) const;
    bool isWall(char ch) const;
    bool isWall(Position position) const;

    void setPlayerInitialPosition(Position position);
    Position playerInitialPosition() const;

    void setGhostInitialPosition(Position position);
    Position ghostInitialPosition() const;

    void setPlayerInitialDirection(const Direction& direction);
    const Direction& playerInitialDirection() const;

    int dots() const;

    void render(Window* window) const;
};

#endif
