#include "engine/ncurses.hpp"

NCurses::NCurses()
{
    // determines the terminal type and initializes the curses SCREEN, WINDOW, and other data structures
    initscr();

    // disables line buffering so characters typed are available immediately to the program
    cbreak();

    // prevents typed characters from being automatically echoed to the screen
    noecho();

    // adjusts the cursor visibility
    curs_set(0);

    // enables recognition of a terminal's function keys (like arrows, F2-F12)
    keypad(stdscr, true);

    // makes getch() non-blocking. If no input is ready, getch() returns ERR instead of waiting until a key is pressed.
    nodelay(stdscr, true);

    // sets the delay for recognizing an escape sequence to 0 millisecons
    set_escdelay(0);

    if (has_colors())
    {
        start_color();
        init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
        init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
        init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
        init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
    }

    clear();   // clears the screen completely on the next call to refresh()
    refresh(); // gets actual output to the terminal, as other routines merely manipulate data structures
}

NCurses::~NCurses()
{
    endwin(); // cleans up ncurses and returns terminal to default mode
}
