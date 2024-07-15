#ifndef MENUITEMSERVICE_H
#define MENUITEMSERVICE_H

#include"../DAO/IMenuItemDAO.h"
#include<memory>

class MenuItemService
{
public:
    MenuItemService(std::unique_ptr<IMenuItemDAO> menuItemDAO);
    bool addMenuItem(const MenuItem& menuItem);
    bool updateMenuItem(const MenuItem& menuItem);
    MenuItem deleteMenuItemById(int menuItemId);
    MenuItem getMenuItemById(int menuItemId);
    std::vector<MenuItem> getAllMenuItems();
private:
    std::unique_ptr<IMenuItemDAO> menuItemDAO;
};
#endif