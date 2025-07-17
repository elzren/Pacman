#include "engine/ncurses.hpp"

NCurses::NCurses()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    set_escdelay(0);

    if(has_colors())
    {
        start_color();
		init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
		init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
        init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
		init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
    }

    clear();
    refresh();
}

NCurses::~NCurses()
{
    endwin();
}
