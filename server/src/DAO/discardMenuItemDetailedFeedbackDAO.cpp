#include "../../inc/DAO/discardMenuItemDetailedFeedbackDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

DiscardMenuItemDetailedFeedbackDAO::DiscardMenuItemDetailedFeedbackDAO() : databaseConnection{DatabaseConnection::getInstance()} {}

int DiscardMenuItemDetailedFeedbackDAO::addFeedback(const DiscardMenuItemDetailedFeedback& feedback) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("INSERT INTO discardMenuItemDetailedFeedback (userId, menuItemId, whatYouLiked, howWouldItTaste, shareRecipe) VALUES (?, ?, ?, ?, ?)"));
        pstmt->setUInt64(1, feedback.userId);
        pstmt->setUInt64(2, feedback.menuItemId);
        pstmt->setString(3, feedback.whatYouLiked);
        pstmt->setString(4, feedback.howWouldItTaste);
        pstmt->setString(5, feedback.shareRecipe);
        int updateCount = pstmt->executeUpdate();

        if (updateCount == 0) {
            std::cerr << "Failed to add feedback." << std::endl;
            return -1;
        }

        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        std::unique_ptr<sql::ResultSet> rs(stmt->executeQuery("SELECT LAST_INSERT_ID()"));

        int newFeedbackId = -1;
        if (rs->next()) {
            newFeedbackId = rs->getInt(1); 
        } else {
            std::cerr << "Failed to retrieve last inserted id." << std::endl;
        }

        return newFeedbackId;
    } catch (const sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;

       
    }
    return -1;
}

DiscardMenuItemDetailedFeedback DiscardMenuItemDetailedFeedbackDAO::getFeedbackById(const int& id) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM discardMenuItemDetailedFeedback WHERE id = ?"));
        pstmt->setInt(1, id);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            return DiscardMenuItemDetailedFeedback(
                res->getInt("id"),
                res->getUInt64("userId"),
                res->getUInt64("menuItemId"),
                res->getString("whatYouLiked"),
                res->getString("howWouldItTaste"),
                res->getString("shareRecipe")
            );
        }
    } catch (const sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return DiscardMenuItemDetailedFeedback();
}

std::vector<DiscardMenuItemDetailedFeedback> DiscardMenuItemDetailedFeedbackDAO::getAllFeedbacks() {
    std::vector<DiscardMenuItemDetailedFeedback> feedbacks;

    try {
        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM discardMenuItemDetailedFeedback"));

        while (res->next()) {
            feedbacks.push_back(DiscardMenuItemDetailedFeedback(
                res->getInt("id"),
                res->getUInt64("userId"),
                res->getUInt64("menuItemId"),
                res->getString("whatYouLiked"),
                res->getString("howWouldItTaste"),
                res->getString("shareRecipe")
            ));
        }
    } catch (const sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return feedbacks;
}
