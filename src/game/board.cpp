#include "game/board.hpp"
#include "engine/ncurses.hpp"

void Board::setBoard(const std::vector<std::vector<char>>& board)
{
    m_height = board.size();
    m_width = m_height ? board[0].size() : 0;

    m_board.resize(m_height, std::vector<char>(m_width, ' '));

    for (size_t row{0}; row < board.size(); ++row)
    {
        for (size_t column{0}; column < board[row].size(); ++column)
        {
            if (static_cast<int>(column) < m_width)
                m_board[row][column] = board[row][column];
        }
    }
}

int Board::getHeight() const { return m_height; }
int Board::getWidth() const { return m_width; }

void Board::render(Window* window) const
{
    if (window)
    {
        window->erase();
        for (size_t row{0}; row < m_board.size(); ++row)
        {
            for (size_t column{0}; column < m_board[row].size(); ++column)
            {
                if (isVisibleWall(m_board[row][column]))
                {
                    window->addChar(column, row, ' ', NCurses::CYAN_CYAN);
                }
                else if (isInvisibleWall(m_board[row][column]))
                {
                    window->addChar(column, row, ' ');
                }
                else
                {
                    window->addChar(column, row, m_board[row][column]);
                }
            }
        }
        window->refresh();
    }
}

bool Board::isVisibleWall(char ch) const { return ch == '#'; }
bool Board::isInvisibleWall(char ch) const { return ch == 'x'; }
bool Board::isWall(char ch) const
{
    return isVisibleWall(ch) || isInvisibleWall(ch);
}
