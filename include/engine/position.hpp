#ifndef POSITION_HPP
#define POSITION_HPP

struct Position
{
    int x{};
    int y{};

    bool operator==(Position other) { return x == other.x && y == other.y; }
};

#endif
