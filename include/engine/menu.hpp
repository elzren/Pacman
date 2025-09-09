#ifndef MENU_HPP
#define MENU_HPP

#include "engine/menuItem.hpp"
#include "engine/window.hpp"
#include <vector>

class Menu
{
  private:
    std::vector<MenuItem> m_items{};
    size_t m_currentIndex{0};
    MenuItem* m_currentItem{nullptr};

  public:
    Menu() = default;

    void addItem(const MenuItem& item);
    MenuItem* currentItem();

    void handleInput(int input);
    void render(Window* win);

    void moveUp();
    void moveDown();
};

#endif
