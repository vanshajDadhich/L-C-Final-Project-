#ifndef IMENUITEMDAO_H
#define IMENUITEMDAO_H

#include "../DTO/menuItem.h"
#include <vector>

class IMenuItemDAO {
public:
    virtual MenuItem getMenuItemById(const int& menuItemId) = 0;
    virtual std::vector<MenuItem> getAllMenuItems() = 0;
    virtual std::vector<MenuItem> getMenuItemByType(MenuItemType type) = 0;
    virtual bool addMenuItem(const MenuItem& menuItem) = 0;
    virtual bool updateMenuItem(const MenuItem& menuItem) = 0;
    virtual MenuItem deleteMenuItem(const int& menuItemId) = 0;
};

#endif