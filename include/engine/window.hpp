#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "engine/ncurses.hpp"
#include <ncurses.h>
#include <string>

class Window
{
  private:
    WINDOW* m_window{nullptr};

    int m_width{};
    int m_height{};

    bool m_border{true};

    std::string m_topLabel{};
    std::string m_bottomLabel{};

  public:
    Window(int width, int height, int startX, int startY, bool border = true);
    Window(Window* parentWin, int width, int height, int startX, int startY,
           bool border = false);
    ~Window();

    void erase();
    void refresh();

    void addChar(int x, int y, int ch);
    void addChar(int x, int y, int ch, NCurses::ColorPair colorPair);
    void addString(int x, int y, const std::string& str);

    void setTopLabel(std::string_view label);
    void setBottomLabel(std::string_view label);

    int getWidth() const;
    int getHeight() const;
};

#endif
