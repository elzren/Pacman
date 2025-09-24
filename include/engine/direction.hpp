#ifndef DIRECTION_HPP
#define DIRECTION_HPP

class Direction
{
  public:
    enum Type
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

  private:
    Type m_type{};

  public:
    Direction(Type type);

    Type type() const;
    Direction operator-() const;
    friend bool operator<(const Direction& first, const Direction& second);
};

#endif
