#ifndef MENUITEMSERVICE_H
#define MENUITEMSERVICE_H

#include"../DAO/IMenuItemDAO.h"

class MenuItemService
{
public:
    MenuItemService(IMenuItemDAO* menuItemDAO);
    bool addMenuItem(const MenuItem& menuItem);
    bool updateMenuItem(const MenuItem& menuItem);
    bool deleteMenuItemByID(int menuItemId);
    MenuItem getMenuItemById(int menuItemId);
    std::vector<MenuItem> getAllMenuItems();
private:
    IMenuItemDAO* menuItemDAO;
};
#endif