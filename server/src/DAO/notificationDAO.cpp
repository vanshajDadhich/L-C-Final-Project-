#include "../../inc/DAO/notificationDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

NotificationDAO::NotificationDAO() : databaseConnection{DatabaseConnection::getInstance()} {}

std::vector<Notification> NotificationDAO::getAllNotifications() {
    std::vector<Notification> notifications;

    try {
        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM Notification"));

        while (res->next()) {
            notifications.push_back(Notification(
                res->getInt("notificationId"),
                res->getString("notificationTitle"),
                res->getString("message"),
                res->getString("date")
            ));
        }
    } catch (const sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return notifications;
}

Notification NotificationDAO::getNotificationById(const int& notificationId) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM Notification WHERE notificationId = ?"));
        pstmt->setInt(1, notificationId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            return Notification(
                res->getInt("notificationId"),
                res->getString("notificationTitle"),
                res->getString("message"),
                res->getString("date")
            );
        }
    } catch (const sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return Notification(0, "", "", "");
}

bool NotificationDAO::addNotification(const Notification& notification) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("INSERT INTO Notification (notificationTitle, message) VALUES (?, ?)"));
        pstmt->setString(1, notification.notificationTitle);
        pstmt->setString(2, notification.message);
        pstmt->executeUpdate();

        return true;
    } catch (const sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}

bool NotificationDAO::deleteNotification(const int& notificationId) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("DELETE FROM Notification WHERE notificationId = ?"));
        pstmt->setInt(1, notificationId);
        pstmt->executeUpdate();
        return true;
    } catch (const sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}

std::vector<Notification> NotificationDAO::getAllNotificationsFromId(const int& userId) {
    std::vector<Notification> notifications;

    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM Notification WHERE userId = ?"));
        pstmt->setInt(1, userId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            notifications.push_back(Notification(
                res->getInt("notificationId"),
                res->getString("notificationTitle"),
                res->getString("message"),
                res->getString("date")
            ));
        }
    } catch (const sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return notifications;
}
