#include "../../inc/DAO/nextDayMenuVotingDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

NextDayMenuVotingDAO::NextDayMenuVotingDAO() : databaseConnection{DatabaseConnection::getInstance()} {}

bool NextDayMenuVotingDAO::addNextDayMenuRollout(const std::vector<NextDayMenuVoting>& nextDayMenus) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement(
                "INSERT INTO NextDayMenuVoting (menuItemId, voteCount, rating, sentiments) VALUES (?, ?, ?, ?)"));
        
        for (const auto& menu : nextDayMenus) {
            pstmt->setInt(1, menu.menuItemId);
            pstmt->setInt(2, menu.voteCount);
            pstmt->setDouble(3, menu.rating);
            pstmt->setString(4, menu.sentiments);
            pstmt->executeUpdate();
        }

        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}

std::vector<NextDayMenuVoting> NextDayMenuVotingDAO::getAllNextDayMenuRollOutItem() {
    std::vector<NextDayMenuVoting> nextDayMenus;

    try {
        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM NextDayMenuVoting"));

        while (res->next()) {
            nextDayMenus.push_back(NextDayMenuVoting(
                res->getInt("menuItemId"),
                res->getInt("voteCount"),
                res->getDouble("rating"),
                res->getString("sentiments")
            ));
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return nextDayMenus;
}

bool NextDayMenuVotingDAO::increaseVoteCountForMenuItemId(const int& menuItemId) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement(
                "UPDATE NextDayMenuVoting SET voteCount = voteCount + 1 WHERE menuItemId = ?"));
        pstmt->setInt(1, menuItemId);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}

bool NextDayMenuVotingDAO::deleteMenuRolledOut() {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("DELETE FROM NextDayMenuVoting"));
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}

int NextDayMenuVotingDAO::getMostVotedMenuItemIdForMenuType(MenuItemType menuItemType) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement(
                "SELECT menuItemId FROM NextDayMenuVoting WHERE menuItemId IN "
                "(SELECT menuItemId FROM MenuItem WHERE menuItemType = ?) "
                "ORDER BY voteCount DESC LIMIT 1"));
        pstmt->setInt(1, static_cast<int>(menuItemType));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            return res->getInt("menuItemId");
        }
        
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return -1;
}
