#include "../../inc/DAO/feedbackDAO.h"
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>

FeedbackDAO::FeedbackDAO() : databaseConnection{DatabaseConnection::getInstance()} {}

bool FeedbackDAO::addFeedback(const Feedback& feedback) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement(
                "INSERT INTO Feedback (userId, menuItemId, rating, comment, timestamp) VALUES (?, ?, ?, ?, ?)"));
        pstmt->setInt(1, feedback.userId);
        pstmt->setInt(2, feedback.menuItemId);
        pstmt->setInt(3, feedback.rating);
        pstmt->setString(4, feedback.comment);
        pstmt->setString(5, feedback.date);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}

bool FeedbackDAO::deleteFeedbackByID(const int& feedbackId) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("DELETE FROM Feedback WHERE feedbackId = ?"));
        pstmt->setInt(1, feedbackId);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}

Feedback FeedbackDAO::getFeedbackById(const int& feedbackId) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM Feedback WHERE feedbackId = ?"));
        pstmt->setInt(1, feedbackId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            return Feedback(
                feedbackId,
                res->getInt("userId"),
                res->getInt("menuItemId"),
                res->getInt("rating"),
                res->getString("comment"),
                res->getString("timestamp")
            );
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return Feedback(0, 0, 0, 0, "", "");
}

std::vector<Feedback> FeedbackDAO::getFeedbacksByMenuItemId(const int& menuItemId) {
    std::vector<Feedback> feedbacks;
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM Feedback WHERE menuItemId = ?"));
        pstmt->setInt(1, menuItemId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            feedbacks.emplace_back(
                res->getInt("feedbackId"),
                res->getInt("userId"),
                res->getInt("menuItemId"),
                res->getInt("rating"),
                res->getString("comment"),
                res->getString("timestamp")
            );
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return feedbacks;
}

std::vector<Feedback> FeedbackDAO::getAllFeedbacks() {
    std::vector<Feedback> feedbacks;
    try {
        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM Feedback"));

        while (res->next()) {
            feedbacks.emplace_back(
                res->getInt("feedbackId"),
                res->getInt("userId"),
                res->getInt("menuItemId"),
                res->getInt("rating"),
                res->getString("comment"),
                res->getString("timestamp")
            );
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return feedbacks;
}

std::vector<Feedback> FeedbackDAO::getFeedbacksForMenuType(MenuItemType menuItemType) {
    std::vector<Feedback> feedbacks;
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement(
                "SELECT * FROM Feedback WHERE menuItemId IN (SELECT menuItemId FROM MenuItem WHERE menuItemType = ?)"));
        pstmt->setInt(1, menuItemType);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            feedbacks.emplace_back(
                res->getInt("feedbackId"),
                res->getInt("userId"),
                res->getInt("menuItemId"),
                res->getInt("rating"),
                res->getString("comment"),
                res->getString("timestamp")
            );
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return feedbacks;
}