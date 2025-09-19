#include "engine/menu.hpp"
#include <ncurses.h>

void Menu::addItem(const MenuItem& item)
{
    m_items.push_back(item);
    m_currentItem = &m_items[m_currentIndex];
}
MenuItem* Menu::currentItem() { return m_currentItem; }

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

void Menu::render(Window* win, int startX, int startY)
{
    if (win)
    {
        win->erase();

        for (size_t i{0}; i < m_items.size(); ++i)
        {
            if (i == m_currentIndex)
            {
                win->addChar(startX, startY + i, '>');
            }
            win->addString(startX + 2, startY + i, m_items[i].label);
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
