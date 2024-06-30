#ifndef MENUITEMDAO_H
#define MENUITEMDAO_H

#include "IMenuItemDAO.h"
#include <vector>
#include "databaseConnection.h"


class MenuItemDAO : public IMenuItemDAO {
public:
    MenuItemDAO();

    MenuItem getMenuItemByID(const int& menuItemId);

    std::vector<MenuItem> getAllMenuItems();

    std::vector<MenuItem> getMenuItemByType(MenuItemType type);

    bool addMenuItem(const MenuItem& menuItem);

    bool updateMenuItem(const MenuItem& menuItem);

    MenuItem deleteMenuItem(const int& menuItemId);

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};

#endif // MENUITEMDAO_H