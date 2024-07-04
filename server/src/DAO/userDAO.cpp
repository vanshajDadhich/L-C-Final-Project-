#include "../../inc/DAO/userDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

UserDAO::UserDAO() : databaseConnection{DatabaseConnection::getInstance()} {}

int UserDAO::addUser(const User& user) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("INSERT INTO User (userName, password, Role) VALUES (?, ?, ?)"));
        pstmt->setString(1, user.name);
        pstmt->setString(2, user.password);
        pstmt->setInt(3, static_cast<int>(user.role));
        int updateCount = pstmt->executeUpdate();

        if (updateCount == 0) {
            std::cerr << "Failed to add user." << std::endl;
            return -1;
        }

        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery("SELECT LAST_INSERT_ID()"));

        int newUserId = -1;
        if (rs->next()) {
            newUserId = rs->getInt(1);
        } else {
            std::cerr << "Failed to retrieve last inserted id." << std::endl;
        }

        return newUserId;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return -1;
    }
}

User UserDAO::getUserByID(const int& userId) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM User WHERE userId = ?"));
        pstmt->setInt(1, userId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            return User(
                res->getInt("userId"),
                res->getString("userName"),
                res->getInt("Role"),
                res->getString("password")
            );
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return User(0, "", 0, "");
}

std::vector<User> UserDAO::getAllUsers() {
    std::vector<User> users;

    try {
        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM User"));

        while (res->next()) {
            users.push_back(User(
                res->getInt("userId"),
                res->getString("userName"),
                res->getInt("Role"),
                res->getString("password")
            ));
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return users;
}
