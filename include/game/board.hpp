#ifndef BOARD_HPP
#define BOARD_HPP

#include "engine/window.hpp"
#include <vector>

class Board
{
  private:
    std::vector<std::vector<char>> m_board{};
    int m_height{};
    int m_width{};

  public:
    Board() = default;

    void setBoard(const std::vector<std::vector<char>>& board);

    int getHeight() const;
    int getWidth() const;

    void render(Window* window) const;

    bool isVisibleWall(char ch) const;
    bool isInvisibleWall(char ch) const;
    bool isWall(char ch) const;
};

#endif