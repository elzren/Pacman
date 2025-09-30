#include "game/ghost.hpp"
#include "engine/direction.hpp"
#include "engine/ncurses.hpp"
#include "engine/random.hpp"
#include "game/player.hpp"
#include <iterator>
#include <set>

Ghost::Ghost(Position position) : m_position{position} {}

void Ghost::setPosition(Position position) { m_position = position; }
void Ghost::setDirection(const Direction& direction)
{
    m_direction = direction;
}

void Ghost::makeFrightened() { m_frightened = true; }
void Ghost::makeUnfrightened() { m_frightened = false; }

Position Ghost::getPosition() const { return m_position; }

bool Ghost::isFrightened() const { return m_frightened; }

Position Ghost::getNextPosition(const Direction& direction) const
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

std::set<Direction> Ghost::availableDirections(const Board& board) const
{
    std::set<Direction> directions{};

    if (!board.isWall(getNextPosition(Direction::LEFT)))
    {
        directions.insert(Direction{Direction::LEFT});
    }
    if (!board.isWall(getNextPosition(Direction::RIGHT)))
    {
        directions.insert(Direction{Direction::RIGHT});
    }
    if (!board.isWall(getNextPosition(Direction::UP)))
    {
        directions.insert(Direction{Direction::UP});
    }
    if (!board.isWall(getNextPosition(Direction::DOWN)))
    {
        directions.insert(Direction{Direction::DOWN});
    }

    eraseDirection(-m_direction,
                   directions); // Remove opposite of current direction
    return directions;
}

void Ghost::move(const std::set<Direction>& availableDirections)
{
    if (!availableDirections.empty())
    {
        auto directionIt = availableDirections.begin();
        std::advance(directionIt,
                     Random::get(0, availableDirections.size() - 1));

        m_direction = *directionIt;
        m_position = getNextPosition(m_direction);
    }
}

void Ghost::eraseDirection(const Direction& direction,
                           std::set<Direction>& directions) const
{
    if (directions.size() > 1)
    {
        directions.erase(direction);
    }
}

void Ghost::update(const Board& board, [[maybe_unused]] const Player& player)
{
    std::set<Direction> availDirections{availableDirections(board)};
    move(availDirections);
}

void Ghost::render(Window* window)
{
    if (window)
    {
        window->addChar(m_position.x, m_position.y, 'M',
                        NCurses::GREEN_DEFAULT);
    }
}

void Ghost::render(Window* window, NCurses::ColorPair colorPair)
{
    if (window)
    {
        window->addChar(m_position.x, m_position.y, 'M', colorPair);
    }
}
