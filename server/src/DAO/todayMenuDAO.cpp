#include "../../inc/DAO/todayMenuDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

TodayMenuDAO::TodayMenuDAO() : databaseConnection{DatabaseConnection::getInstance()} {}

bool TodayMenuDAO::addTodayMenu(const std::vector<int>& todayDayMenuItemId) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("INSERT INTO todayMenu (menuItemId) VALUES (?)"));

        for (const int& menuItemId : todayDayMenuItemId) {
            pstmt->setInt(1, menuItemId);
            pstmt->executeUpdate();
        }

        return true;
    } catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}

std::vector<MenuItem> TodayMenuDAO::getAllTodayMenuItem() {
    std::vector<MenuItem> todayMenuItems;

    try {
        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT MenuItem.* FROM todayMenu JOIN MenuItem ON todayMenu.menuItemId = MenuItem.menuItemId"));

        while (res->next()) {
            todayMenuItems.push_back(MenuItem(
                res->getInt("menuItemId"),
                res->getString("menuItemName"),
                static_cast<MenuItemType>(res->getInt("menuItemType")),
                res->getBoolean("availability"),
                res->getInt("price")
            ));
        }
    } catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return todayMenuItems;
}

bool TodayMenuDAO::deleteTodayMenu() {
    try {
        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        stmt->executeUpdate("DELETE FROM todayMenu");
        return true;
    } catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}
