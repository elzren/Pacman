#ifndef WINDOW_HPP
#define WINDOW_HPP

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
    ~Window();

    void erase();
    void refresh();

    void addChar(int x, int y, int ch);
    void addString(int x, int y, const std::string& str);

    void setTopLabel(std::string_view label);
    void setBottomLabel(std::string_view label);
};

#endif
