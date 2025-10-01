#include "engine/menu.hpp"
#include "engine/ncurses.hpp"
#include <ncurses.h>

void Menu::addItem(const MenuItem& item)
{
    m_items.push_back(item);
    m_currentItem = &m_items[m_currentIndex];
}
const MenuItem* Menu::currentItem() const { return m_currentItem; }

void Menu::handleInput(int input)
{
    switch (input)
    {
    case 'k':
    case KEY_UP:
        moveUp();
        break;
    case 'j':
    case KEY_DOWN:
        moveDown();
        break;
    }
}

void Menu::render(Window* win, int startX, int startY, int selectedIndex)
{
    if (win)
    {
        win->erase();

        for (size_t i{0}; i < m_items.size(); ++i)
        {
            if (i == m_currentIndex)
            {
                win->addChar(startX, startY + i, '>', NCurses::MAGENTA_DEFAULT);
            }
            if (static_cast<int>(i) == selectedIndex)
            {
                win->addString(startX + 2, startY + i, m_items[i].label,
                               NCurses::BLUE_DEFAULT);
            }
            else
            {
                win->addString(startX + 2, startY + i, m_items[i].label);
            }
        }

        win->refresh();
    }
}

void Menu::moveUp()
{
    if (m_currentIndex > 0)
    {
        --m_currentIndex;
        m_currentItem = &m_items[m_currentIndex];
    }
};

void Menu::moveDown()
{
    if (m_currentIndex + 1 < m_items.size())
    {
        ++m_currentIndex;
        m_currentItem = &m_items[m_currentIndex];
    }
};

int Menu::itemsCount() const { return m_items.size(); }
