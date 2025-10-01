#include "game/player.hpp"
#include "engine/ncurses.hpp"
#include "engine/position.hpp"
#include "game/ghostManager.hpp"
#include <ncurses.h>

void Player::setPosition(Position position) { m_position = position; }
void Player::setDirection(const Direction& direction)
{
    m_direction = direction;
}

Position Player::getNextPosition(const Direction& direction) const
{
    Position nextPosition{m_position};

    switch (direction.type())
    {
    case Direction::LEFT:
        --nextPosition.x;
        break;
    case Direction::RIGHT:
        ++nextPosition.x;
        break;
    case Direction::UP:
        --nextPosition.y;
        break;
    case Direction::DOWN:
        ++nextPosition.y;
        break;
    }

    return nextPosition;
}

Position Player::getPosition() const { return m_position; }

char Player::getSymbol() const
{
    switch (m_direction.type())
    {
    case Direction::LEFT:
        return '>';
    case Direction::RIGHT:
        return '<';
    case Direction::UP:
        return 'v';
    case Direction::DOWN:
        return '^';
    default:
        return '>';
    }
}

bool Player::notFacingWall(const Direction& direction, const Board& board) const
{
    return !board.isWall(getNextPosition(direction));
}

int Player::lives() const { return m_lives; }

int Player::score() const { return m_score; }

bool Player::eatenAllDots(int totalDots) const
{
    return m_dotsEaten == totalDots;
}

void Player::eatDot(Board& board, GhostManager& ghostMgr)
{
    if (board.isSmallDot(m_position))
    {
        ++m_dotsEaten;
        board.setTile(m_position, ' ');
        incrementScore(10);
    }
    else if (board.isBigDot(m_position))
    {
        ++m_dotsEaten;
        board.setTile(m_position, ' ');
        incrementScore(50);

        ghostMgr.setFrightenedMode();
    }
}

void Player::kill() { --m_lives; }

void Player::incrementScore(int score) { m_score += score; }

void Player::handleInput(int input)
{
    switch (input)
    {
    case 'h':
    case KEY_LEFT:
        m_inputDirection = Direction::LEFT;
        break;
    case 'l':
    case KEY_RIGHT:
        m_inputDirection = Direction::RIGHT;
        break;
    case 'k':
    case KEY_UP:
        m_inputDirection = Direction::UP;
        break;
    case 'j':
    case KEY_DOWN:
        m_inputDirection = Direction::DOWN;
        break;
    }
}

void Player::update(Board& board)
{
    if (m_inputDirection && notFacingWall(*m_inputDirection, board))
    {
        Position nextPosition{getNextPosition(*m_inputDirection)};

        m_position = nextPosition;
        m_direction = *m_inputDirection;
        m_inputDirection = std::nullopt;
    }
    else if (notFacingWall(m_direction, board))
    {
        Position nextPosition{getNextPosition(m_direction)};

        m_position = nextPosition;
    }
}

void Player::render(Window* window)
{
    if (window && m_lives > 0)
    {
        window->addChar(m_position.x, m_position.y, getSymbol(),
                        NCurses::MAGENTA_DEFAULT);
    }
}
