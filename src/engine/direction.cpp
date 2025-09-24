#include "engine/direction.hpp"
#include <cassert>

Direction::Direction(Type type) : m_type{type} {}

Direction::Type Direction::type() const { return m_type; }

Direction Direction::operator-() const
{
    switch (m_type)
    {
    case LEFT:
        return Direction{RIGHT};
    case RIGHT:
        return Direction{LEFT};
    case UP:
        return Direction{DOWN};
    case DOWN:
        return Direction{UP};
    default:
        break;
    }

    assert(0 && "Invalid direction");
    return Direction{UP};
}

bool operator<(const Direction& first, const Direction& second)
{
    return first.m_type < second.m_type;
}
