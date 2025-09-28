#ifndef NCURSES_HPP
#define NCURSES_HPP

#include <ncurses.h>

class NCurses
{
  public:
    enum ColorPair
    {
        BLUE_DEFAULT = 1,
        GREEN_DEFAULT,
        RED_DEFAULT,
        MAGENTA_DEFAULT,
        YELLOW_DEFAULT,
        WHITE_DEFAULT,
        BLUE_BLUE,
        CYAN_CYAN,
    };

  public:
    NCurses();
    ~NCurses();
};

#endif
