#include "game/chaserGhost.hpp"
#include "engine/direction.hpp"
#include "engine/ncurses.hpp"
#include "engine/position.hpp"
#include "game/board.hpp"
#include "game/player.hpp"

ChaserGhost::ChaserGhost(Position position) : Ghost{position} {}

void ChaserGhost::eraseDirectionsAwayFromPlayer(std::set<Direction>& directions,
                                                Position playerPosition)
{
    if (m_position.y > playerPosition.y)
    {
        eraseDirection(Direction::DOWN, directions);
    }
    else if (m_position.y < playerPosition.y)
    {
        eraseDirection(Direction::UP, directions);
    }
    else
    {
        eraseDirection(Direction::DOWN, directions);
        eraseDirection(Direction::UP, directions);
    }

    if (m_position.x > playerPosition.x)
    {
        eraseDirection(Direction::RIGHT, directions);
    }
    else if (m_position.x < playerPosition.x)
    {
        eraseDirection(Direction::LEFT, directions);
    }
    else
    {
        eraseDirection(Direction::RIGHT, directions);
        eraseDirection(Direction::LEFT, directions);
    }
}

void ChaserGhost::update(const Board& board, const Player& player)
{
    std::set<Direction> availDirections{availableDirections(board)};

    if (!m_frightened && availDirections.size() > 1)
    {
        eraseDirectionsAwayFromPlayer(availDirections, player.getPosition());
    }

    move(availDirections);
}

void ChaserGhost::render(Window* window)
{
    if (window)
    {
        window->addChar(m_position.x, m_position.y, 'X', NCurses::RED_DEFAULT);
    }
}

void ChaserGhost::render(Window* window, NCurses::ColorPair colorPair)
{
    if (window)
    {
        window->addChar(m_position.x, m_position.y, 'X', colorPair);
    }
}
