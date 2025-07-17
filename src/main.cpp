#include "engine/ncurses.hpp"
#include <thread>
#include <chrono>

int main()
{
    NCurses ncurses;

    int input{};
    int x{5};
    int y{5};

    while(input != 'q')
    {
        input = getch();

        switch (input)
        {
        case KEY_UP:
        case 'w':
            --y;
            break;
        case KEY_DOWN:
        case 's':
            ++y;
            break;
        case KEY_LEFT:
        case 'a':
            --x;
            break;
        case KEY_RIGHT:
        case 'd':
            ++x;
            break;
        default:
            break;
        }

        erase();
        wattron(stdscr, COLOR_PAIR(NCurses::BLUE_BLACK));
        mvaddch(y, x, '0');
        wattroff(stdscr, COLOR_PAIR(NCurses::BLUE_BLACK));
        refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    return 0;
}
