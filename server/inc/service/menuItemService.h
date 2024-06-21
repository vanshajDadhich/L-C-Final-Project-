#ifndef MENUITEMSERVICE_H
#define MENUITEMSERVICE_H

#include"../DAO/IMenuItemDAO.h"

class MenuItemService
{
public:
    MenuItemService(IMenuItemDAO* menuItemDAO);
    bool addMenuItem(std::vector<std::string> menuData);
    bool updateMenuItem(const MenuItem& menuItem);
    bool deleteMenuItemByID(int menuItemId);
    MenuItem getMenuItemById(int menuItemId);
    std::vector<std::vector<std::string>> getAllMenuItems();
private:
    IMenuItemDAO* menuItemDAO;
};
#endif