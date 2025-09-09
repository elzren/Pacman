#ifndef MENU_ITEM_HPP
#define MENU_ITEM_HPP

#include <string>

struct MenuItem
{
    enum ItemId
    {
        START,
        EXIT
    };

    ItemId id{};
    std::string label{};
};

#endif
