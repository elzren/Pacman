#include "game/oneEyedGhost.hpp"
#include "engine/direction.hpp"
#include "game/ghost.hpp"
#include <algorithm>
#include <optional>

OneEyedGhost::OneEyedGhost(Position position) : Ghost{position} {}

std::optional<Direction>
OneEyedGhost::getDirectionTowardsInSightPlayer(Position playerPosition,
                                               const Board& board)
{
    int ghostX = m_position.x;
    int ghostY = m_position.y;
    int playerX = playerPosition.x;
    int playerY = playerPosition.y;

    if (ghostY == playerY)
    {
        for (int i{std::min(ghostX, playerX) + 1};
             i < std::max(ghostX, playerX); ++i)
        {
            if (board.isWall(Position{i, ghostY}))
                return std::nullopt;
        }
        if (ghostX > playerX)
        {
            return Direction{Direction::LEFT};
        }
        if (ghostX < playerX)
        {
            return Direction{Direction::RIGHT};
        }
    }
    else if (ghostX == playerX)
    {
        for (int i{std::min(ghostY, playerY) + 1};
             i < std::max(ghostY, playerY); ++i)
        {
            if (board.isWall(Position{ghostX, i}))
                return std::nullopt;
        }
        if (ghostY > playerY)
        {
            return Direction{Direction::UP};
        }
        if (ghostY < playerY)
        {
            return Direction{Direction::DOWN};
        }
    }

    return std::nullopt;
}

void OneEyedGhost::update(const Board& board, const Player& player)
{
    if (m_frightened)
    {
        Ghost::update(board, player);
    }
    else
    {
        auto directionTowardsInSightPlayer{
            getDirectionTowardsInSightPlayer(player.getPosition(), board)};

        if (directionTowardsInSightPlayer)
        {
            m_direction = *directionTowardsInSightPlayer;
            m_position = getNextPosition(m_direction);
        }
        else
        {
            Ghost::update(board, player);
        }
    }
}

void OneEyedGhost::render(Window* window)
{
    if (window)
    {
        window->addChar(m_position.x, m_position.y, 'Z',
                        NCurses::YELLOW_DEFAULT);
    }
}

void OneEyedGhost::render(Window* window, NCurses::ColorPair colorPair)
{
    if (window)
    {
        window->addChar(m_position.x, m_position.y, 'Z', colorPair);
    }
}
