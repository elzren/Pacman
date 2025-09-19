#ifndef BOARD_HPP
#define BOARD_HPP

#include "engine/position.hpp"
#include "engine/window.hpp"
#include <vector>

class Board
{
  private:
    std::vector<std::vector<char>> m_board{};
    int m_height{};
    int m_width{};
    Position m_playerInitialPosition{};

  public:
    Board() = default;

    void setBoard(const std::vector<std::vector<char>>& board);

    int getHeight() const;
    int getWidth() const;

    char getTile(Position position) const;
    void setTile(Position position, char ch);

    bool isVisibleWall(char ch) const;
    bool isInvisibleWall(char ch) const;
    bool isWall(char ch) const;
    bool isWall(Position position) const;

    void setPlayerInitialPosition(Position position);
    Position playerInititalPosition();

    void render(Window* window) const;
};

#endif
