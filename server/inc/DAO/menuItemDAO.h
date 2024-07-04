#ifndef MENUITEMDAO_H
#define MENUITEMDAO_H

#include "IMenuItemDAO.h"
#include "databaseConnection.h"
#include <memory>
#include <vector>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class MenuItemDAO : public IMenuItemDAO {
public:
    MenuItemDAO();

    MenuItem getMenuItemById(const int& menuItemId);
    std::vector<MenuItem> getAllMenuItems();
    std::vector<MenuItem> getMenuItemByType(MenuItemType type);
    bool addMenuItem(const MenuItem& menuItem);
    bool updateMenuItem(const MenuItem& menuItem);
    MenuItem deleteMenuItem(const int& menuItemId);

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;

    MenuItem createMenuItemFromResultSet(std::unique_ptr<sql::ResultSet>& res);
    void bindMenuItemToStatement(std::unique_ptr<sql::PreparedStatement>& pstmt, const MenuItem& menuItem);

};

#endif
