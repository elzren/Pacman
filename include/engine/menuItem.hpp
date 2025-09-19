#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include <string>

struct MenuItem
{
    enum ItemId
    {
        START,
        EXIT,
        RESUME,
        RESTART,
        MAIN_MENU
    };

    ItemId id{};
    std::string label{};
};

#endif
