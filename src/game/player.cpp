#include "game/player.hpp"
#include "engine/position.hpp"
#include <ncurses.h>

void Player::setPosition(Position position) { m_position = position; }
void Player::setDirection(Direction direction) { m_direction = direction; }

Position Player::getNextPosition(Direction direction) const
{
    Position nextPosition{m_position};

    switch (direction)
    {
    case LEFT:
        --nextPosition.x;
        break;
    case RIGHT:
        ++nextPosition.x;
        break;
    case UP:
        --nextPosition.y;
        break;
    case DOWN:
        ++nextPosition.y;
        break;
    }

    return nextPosition;
}

char Player::getSymbol() const
{
    switch (m_direction)
    {
    case LEFT:
        return '>';
    case RIGHT:
        return '<';
    case UP:
        return 'v';
    case DOWN:
        return '^';
    default:
        return '>';
    }
}

bool Player::notFacingWall(Player::Direction direction,
                           const Board& board) const
{
    return !board.isWall(getNextPosition(direction));
}

void Player::eatItem(Board& board) { board.setTile(m_position, ' '); }

void Player::handleInput(int input)
{
    switch (input)
    {
    case 'h':
    case KEY_LEFT:
        m_inputDirection = LEFT;
        break;
    case 'l':
    case KEY_RIGHT:
        m_inputDirection = RIGHT;
        break;
    case 'k':
    case KEY_UP:
        m_inputDirection = UP;
        break;
    case 'j':
    case KEY_DOWN:
        m_inputDirection = DOWN;
        break;
    }
}

void Player::update(Board& board)
{
    if (m_inputDirection && notFacingWall(*m_inputDirection, board))
    {
        Position nextPosition{getNextPosition(*m_inputDirection)};

        eatItem(board);

        m_position = nextPosition;
        m_direction = *m_inputDirection;
        m_inputDirection = std::nullopt;
    }
    else if (notFacingWall(m_direction, board))
    {
        Position nextPosition{getNextPosition(m_direction)};

        eatItem(board);

        m_position = nextPosition;
    }
}
void Player::render(Window* window)
{
    if (window)
    {
        window->addChar(m_position.x, m_position.y, getSymbol());
    }
}
