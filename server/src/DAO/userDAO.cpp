#include "../../inc/DAO/userDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

UserDAO::UserDAO() : databaseConnection{DatabaseConnection::getInstance()} {}


bool UserDAO::addUser(const User& user) {
        try {
            std::unique_ptr<sql::PreparedStatement> pstmt(
                databaseConnection->getConnection()->prepareStatement("INSERT INTO User (userId, userName, password, Role) VALUES (?, ?, ?, ?)"));
            pstmt->setInt(1, user.userId);
            pstmt->setString(2, user.name);
            pstmt->setString(3, user.password);
            pstmt->setInt(4, static_cast<int>(user.role));
            pstmt->executeUpdate();
            return true;
        } catch (sql::SQLException &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            return false;
        }
    }

    bool UserDAO::updateUser(const User& user) {
        try {
            std::unique_ptr<sql::PreparedStatement> pstmt(
                databaseConnection->getConnection()->prepareStatement("UPDATE User SET userName = ?, password = ?, Role = ? WHERE userId = ?"));
            pstmt->setString(1, user.name);
            pstmt->setString(2, user.password);
            pstmt->setInt(3, static_cast<int>(user.role));
            pstmt->setInt(4, user.userId);
            pstmt->executeUpdate();
            return true;
        } catch (sql::SQLException &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            return false;
        }
    }

    bool UserDAO::deleteUser(const int& userId) {
        try {
            std::unique_ptr<sql::PreparedStatement> pstmt(
                databaseConnection->getConnection()->prepareStatement("DELETE FROM User WHERE userId = ?"));
            pstmt->setInt(1, userId);
            pstmt->executeUpdate();
            return true;
        } catch (sql::SQLException &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            return false;
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

        // Return a default-constructed User if not found or error
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
