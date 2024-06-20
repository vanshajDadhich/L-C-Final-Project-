#include "../../inc/DAO/RecommendationSelectionDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

RecommendationSelectionDAO::RecommendationSelectionDAO() : databaseConnection{DatabaseConnection::getInstance()} {}


bool RecommendationSelectionDAO::addRecommendationSelection(const RecommendationSelection& selection) {
        try {
            std::unique_ptr<sql::PreparedStatement> pstmt(
                databaseConnection->getConnection()->prepareStatement("INSERT INTO RecommendationSelection (menuItemId, selectionCount, sentimentScore) VALUES (?, ?, ?)"));
            pstmt->setInt(1, selection.menuItemId);
            pstmt->setInt(2, selection.selectionCount);
            pstmt->setInt(3, selection.sentimentScore);
            pstmt->executeUpdate();
            return true;
        } catch (sql::SQLException &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            return false;
        }
    }

    RecommendationSelection RecommendationSelectionDAO::getRecommendationSelectionById(const int& id) {
        try {
            std::unique_ptr<sql::PreparedStatement> pstmt(
                databaseConnection->getConnection()->prepareStatement("SELECT * FROM RecommendationSelection WHERE selectionId = ?"));
            pstmt->setInt(1, id);
            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            if (res->next()) {
                return RecommendationSelection(
                    res->getInt("selectionId"),
                    res->getInt("menuItemId"),
                    res->getInt("selectionCount"),
                    res->getInt("sentimentScore")
                );
            }
        } catch (sql::SQLException &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
        }

        // Return a default-constructed RecommendationSelection if not found or error
        return RecommendationSelection(0, 0, 0, 0);
    }

    bool RecommendationSelectionDAO::deleteRecommendationSelection(const int& id) {
        try {
            std::unique_ptr<sql::PreparedStatement> pstmt(
                databaseConnection->getConnection()->prepareStatement("DELETE FROM RecommendationSelection WHERE selectionId = ?"));
            pstmt->setInt(1, id);
            pstmt->executeUpdate();
            return true;
        } catch (sql::SQLException &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
            return false;
        }
    }

    RecommendationSelection RecommendationSelectionDAO::getRecommendationSelectionByMenuItemId(const int& menuItemId) {
        try {
            std::unique_ptr<sql::PreparedStatement> pstmt(
                databaseConnection->getConnection()->prepareStatement("SELECT * FROM RecommendationSelection WHERE menuItemId = ?"));
            pstmt->setInt(1, menuItemId);
            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            if (res->next()) {
                return RecommendationSelection(
                    res->getInt("selectionId"),
                    res->getInt("menuItemId"),
                    res->getInt("selectionCount"),
                    res->getInt("sentimentScore")
                );
            }
        } catch (sql::SQLException &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
        }

        // Return a default-constructed RecommendationSelection if not found or error
        return RecommendationSelection(0, 0, 0, 0);
    }

    std::vector<RecommendationSelection> RecommendationSelectionDAO::getAllRecommendationSelectionsForMenuType(MenuItemType menuItemType) {
        std::vector<RecommendationSelection> selections;

        try {
            std::unique_ptr<sql::PreparedStatement> pstmt(
                databaseConnection->getConnection()->prepareStatement("SELECT * FROM RecommendationSelection WHERE menuItemId IN (SELECT menuItemId FROM MenuItem WHERE menuItemType = ?)"));
            pstmt->setInt(1, static_cast<int>(menuItemType));
            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

            while (res->next()) {
                selections.push_back(RecommendationSelection(
                    res->getInt("selectionId"),
                    res->getInt("menuItemId"),
                    res->getInt("selectionCount"),
                    res->getInt("sentimentScore")
                ));
            }
        } catch (sql::SQLException &e) {
            std::cerr << "SQL error: " << e.what() << std::endl;
        }

        return selections;
    }