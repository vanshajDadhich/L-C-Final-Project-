#include "../../inc/DAO/menuItemDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

MenuItemDAO::MenuItemDAO() : databaseConnection{DatabaseConnection::getInstance()} {}


MenuItem MenuItemDAO::getMenuItemByID(const int& menuItemId) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM MenuItem WHERE menuItemId = ?"));
        pstmt->setInt(1, menuItemId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            return MenuItem(
                res->getInt("menuItemId"),
                res->getString("menuItemName"),
                res->getInt("menuItemType"),
                res->getBoolean("availability"),
                res->getInt("price")
            );
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    // Return a default-constructed MenuItem if not found or error
    return MenuItem(0, "", 0, false, 0);
}

std::vector<MenuItem> MenuItemDAO::getAllMenuItems() {
    std::vector<MenuItem> menuItems;

    try {
        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM MenuItem"));

        while (res->next()) {
            menuItems.push_back(MenuItem(
                res->getInt("menuItemId"),
                res->getString("menuItemName"),
                res->getInt("menuItemType"),
                res->getBoolean("availability"),
                res->getInt("price")
            ));
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
            menuItems.push_back(MenuItem(
                res->getInt("menuItemId"),
                res->getString("menuItemName"),
                res->getInt("menuItemType"),
                res->getBoolean("availability"),
                res->getInt("price")
            ));
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return menuItems;
}

bool MenuItemDAO::addMenuItem(const MenuItem& menuItem) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("INSERT INTO MenuItem (menuItemName, menuItemType, availability, price) VALUES (?, ?, ?, ?)"));
        pstmt->setString(1, menuItem.menuItemName);
        pstmt->setInt(2, static_cast<int>(menuItem.menuItemType));
        pstmt->setBoolean(3, menuItem.availability);
        pstmt->setInt(4, menuItem.price);
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
            databaseConnection->getConnection()->prepareStatement("UPDATE MenuItem SET menuItemName = ?, menuItemType = ?, availability = ?, price = ? WHERE menuItemId = ?"));
        pstmt->setString(1, menuItem.menuItemName);
        pstmt->setInt(2, static_cast<int>(menuItem.menuItemType));
        pstmt->setBoolean(3, menuItem.availability);
        pstmt->setInt(4, menuItem.price);
        pstmt->setInt(5, menuItem.menuItemId);
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
        
        // Retrieve the deleted menuItem
        std::unique_ptr<sql::PreparedStatement> pstmt2(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM MenuItem WHERE menuItemId = ?"));
        pstmt2->setInt(1, menuItemId);
        std::unique_ptr<sql::ResultSet> res(pstmt2->executeQuery());
        if (res->next()) {
            deletedMenuItem = MenuItem(
                res->getInt("menuItemId"),
                res->getString("menuItemName"),
                res->getInt("menuItemType"),
                res->getBoolean("availability"),
                res->getInt("price")
            );
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }
    return deletedMenuItem;
}
