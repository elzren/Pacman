#ifndef NCURSES_HPP
#define NCURSES_HPP

#include <ncurses.h>

class NCurses
{
  public:
    enum ColorPair
    {
        BLUE_BLACK = 1,
        GREEN_BLACK,
        RED_BLACK,
        WHITE_BLACK,
        BLUE_BLUE,
        CYAN_CYAN,
        BLUE_DEFAULT,
        RED_DEFAULT,
        WHITE_DEFAULT,
    };

  public:
    NCurses();
    ~NCurses();
};

#endif
