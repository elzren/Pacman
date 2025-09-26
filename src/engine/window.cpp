#include "engine/window.hpp"
#include "engine/ncurses.hpp"
#include <ncurses.h>

Window::Window(int width, int height, int startX, int startY, bool border)
    : m_width{width}, m_height{height}, m_border{border}
{
    m_window = newwin(m_height, m_width, startY, startX);
}

Window::Window(Window* parentWin, int width, int height, int startX, int startY,
               bool border)
    : m_width{width}, m_height{height}, m_border{border}
{
    m_window = derwin(parentWin->m_window, m_height, m_width, startY, startX);
}

Window::~Window()
{
    if (m_window)
        delwin(m_window);
}

void Window::erase()
{
    // copy blanks to every position in the window, clearing the screen
    werase(m_window);

    if (m_border)
        box(m_window, 0, 0);

    if (!m_topLabel.empty())
        addString(3, 0, '[' + m_topLabel + ']');
    if (!m_bottomLabel.empty())
        addString(3, m_height - 1, '[' + m_bottomLabel + ']');
}

void Window::refresh() { wrefresh(m_window); }

void Window::addChar(int x, int y, int ch) { mvwaddch(m_window, y, x, ch); }

void Window::addChar(int x, int y, int ch, NCurses::ColorPair colorPair)
{
    wattron(m_window, A_BOLD);
    wattron(m_window, COLOR_PAIR(colorPair));
    mvwaddch(m_window, y, x, ch);
    wattroff(m_window, COLOR_PAIR(colorPair));
    wattroff(m_window, A_BOLD);
}

void Window::addString(int x, int y, const std::string& str)
{
    mvwaddstr(m_window, y, x, str.c_str());
}

void Window::setTopLabel(std::string_view label) { m_topLabel = label; }
void Window::setBottomLabel(std::string_view label) { m_bottomLabel = label; }

int Window::getWidth() const { return m_width; }

int Window::getHeight() const { return m_height; }
