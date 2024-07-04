#include "../../inc/DAO/menuItemDAO.h"
#include <cppconn/exception.h>

MenuItemDAO::MenuItemDAO() : databaseConnection{DatabaseConnection::getInstance()} {}

MenuItem MenuItemDAO::getMenuItemById(const int& menuItemId) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM MenuItem WHERE menuItemId = ?"));
        pstmt->setInt(1, menuItemId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            return createMenuItemFromResultSet(res);
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return MenuItem();
}

std::vector<MenuItem> MenuItemDAO::getAllMenuItems() {
    std::vector<MenuItem> menuItems;

    try {
        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM MenuItem"));

        while (res->next()) {
            menuItems.push_back(createMenuItemFromResultSet(res));
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return menuItems;
}

std::vector<MenuItem> MenuItemDAO::getMenuItemByType(MenuItemType type) {
    std::vector<MenuItem> menuItems;

    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM MenuItem WHERE menuItemType = ?"));
        pstmt->setInt(1, static_cast<int>(type));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            menuItems.push_back(createMenuItemFromResultSet(res));
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return menuItems;
}

bool MenuItemDAO::addMenuItem(const MenuItem& menuItem) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("INSERT INTO MenuItem (menuItemName, menuItemType, availability, price, vegetarianPreference, spiceLevelOption, foodPreference, sweetToothPreference) VALUES (?, ?, ?, ?, ?, ?, ?, ?)"));
        bindMenuItemToStatement(pstmt, menuItem);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}

bool MenuItemDAO::updateMenuItem(const MenuItem& menuItem) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("UPDATE MenuItem SET menuItemName = ?, menuItemType = ?, availability = ?, price = ?, vegetarianPreference = ?, spiceLevelOption = ?, foodPreference = ?, sweetToothPreference = ? WHERE menuItemId = ?"));
        bindMenuItemToStatement(pstmt, menuItem);
        pstmt->setInt(9, menuItem.menuItemId);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}

MenuItem MenuItemDAO::deleteMenuItem(const int& menuItemId) {
    MenuItem deletedMenuItem;
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("DELETE FROM MenuItem WHERE menuItemId = ?"));
        pstmt->setInt(1, menuItemId);
        pstmt->executeUpdate();
        
        std::unique_ptr<sql::PreparedStatement> pstmt2(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM MenuItem WHERE menuItemId = ?"));
        pstmt2->setInt(1, menuItemId);
        std::unique_ptr<sql::ResultSet> res(pstmt2->executeQuery());
        if (res->next()) {
            deletedMenuItem = createMenuItemFromResultSet(res);
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }
    return deletedMenuItem;
}

MenuItem MenuItemDAO::createMenuItemFromResultSet(std::unique_ptr<sql::ResultSet>& res) {
    return MenuItem(
        res->getInt("menuItemId"),
        res->getString("menuItemName"),
        static_cast<MenuItemType>(res->getInt("menuItemType")),
        res->getBoolean("availability"),
        res->getInt("price"),
        static_cast<VegetarianPreference>(res->getInt("vegetarianPreference")),
        static_cast<SpiceLevelOption>(res->getInt("spiceLevelOption")),
        static_cast<FoodPreference>(res->getInt("foodPreference")),
        static_cast<SweetToothPreference>(res->getInt("sweetToothPreference"))
    );
}

void MenuItemDAO::bindMenuItemToStatement(std::unique_ptr<sql::PreparedStatement>& pstmt, const MenuItem& menuItem) {
    pstmt->setString(1, menuItem.menuItemName);
    pstmt->setInt(2, static_cast<int>(menuItem.menuItemType));
    pstmt->setBoolean(3, menuItem.availability);
    pstmt->setInt(4, menuItem.price);
    pstmt->setInt(5, static_cast<int>(menuItem.vegetarianPreference));
    pstmt->setInt(6, static_cast<int>(menuItem.spiceLevelOption));
    pstmt->setInt(7, static_cast<int>(menuItem.foodPreference));
    pstmt->setInt(8, static_cast<int>(menuItem.sweetToothPreference));
}
