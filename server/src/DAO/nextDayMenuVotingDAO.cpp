// #include "../../inc/DAO/nextDayMenuVotingDAO.h"
// #include <cppconn/prepared_statement.h>
// #include <cppconn/resultset.h>
// #include <cppconn/exception.h>
// #include <iostream>

// NextDayMenuVotingDAO::NextDayMenuVotingDAO() : databaseConnection{DatabaseConnection::getInstance()} {}


// bool NextDayMenuVotingDAO::addNextDayMenuVoting(const NextDayMenuVoting& selection) {
//         try {
//             std::unique_ptr<sql::PreparedStatement> pstmt(
//                 databaseConnection->getConnection()->prepareStatement("INSERT INTO NextDayMenuVoting (menuItemId, selectionCount, sentimentScore) VALUES (?, ?, ?)"));
//             pstmt->setInt(1, selection.menuItemId);
//             pstmt->setInt(2, selection.selectionCount);
//             pstmt->setInt(3, selection.sentimentScore);
//             pstmt->executeUpdate();
//             return true;
//         } catch (sql::SQLException &e) {
//             std::cerr << "SQL error: " << e.what() << std::endl;
//             return false;
//         }
//     }

//     NextDayMenuVoting NextDayMenuVotingDAO::getNextDayMenuVotingById(const int& id) {
//         try {
//             std::unique_ptr<sql::PreparedStatement> pstmt(
//                 databaseConnection->getConnection()->prepareStatement("SELECT * FROM NextDayMenuVoting WHERE selectionId = ?"));
//             pstmt->setInt(1, id);
//             std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

//             if (res->next()) {
//                 return NextDayMenuVoting(
//                     res->getInt("selectionId"),
//                     res->getInt("menuItemId"),
//                     res->getInt("selectionCount"),
//                     res->getInt("sentimentScore")
//                 );
//             }
//         } catch (sql::SQLException &e) {
//             std::cerr << "SQL error: " << e.what() << std::endl;
//         }

//         // Return a default-constructed NextDayMenuVoting if not found or error
//         return NextDayMenuVoting(0, 0, 0, 0);
//     }

//     bool NextDayMenuVotingDAO::deleteNextDayMenuVoting(const int& id) {
//         try {
//             std::unique_ptr<sql::PreparedStatement> pstmt(
//                 databaseConnection->getConnection()->prepareStatement("DELETE FROM NextDayMenuVoting WHERE selectionId = ?"));
//             pstmt->setInt(1, id);
//             pstmt->executeUpdate();
//             return true;
//         } catch (sql::SQLException &e) {
//             std::cerr << "SQL error: " << e.what() << std::endl;
//             return false;
//         }
//     }

//     NextDayMenuVoting NextDayMenuVotingDAO::getNextDayMenuVotingByMenuItemId(const int& menuItemId) {
//         try {
//             std::unique_ptr<sql::PreparedStatement> pstmt(
//                 databaseConnection->getConnection()->prepareStatement("SELECT * FROM NextDayMenuVoting WHERE menuItemId = ?"));
//             pstmt->setInt(1, menuItemId);
//             std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

//             if (res->next()) {
//                 return NextDayMenuVoting(
//                     res->getInt("selectionId"),
//                     res->getInt("menuItemId"),
//                     res->getInt("selectionCount"),
//                     res->getInt("sentimentScore")
//                 );
//             }
//         } catch (sql::SQLException &e) {
//             std::cerr << "SQL error: " << e.what() << std::endl;
//         }

//         // Return a default-constructed NextDayMenuVoting if not found or error
//         return NextDayMenuVoting(0, 0, 0, 0);
//     }

//     std::vector<NextDayMenuVoting> NextDayMenuVotingDAO::getAllNextDayMenuVotingsForMenuType(MenuItemType menuItemType) {
//         std::vector<NextDayMenuVoting> selections;

//         try {
//             std::unique_ptr<sql::PreparedStatement> pstmt(
//                 databaseConnection->getConnection()->prepareStatement("SELECT * FROM NextDayMenuVoting WHERE menuItemId IN (SELECT menuItemId FROM MenuItem WHERE menuItemType = ?)"));
//             pstmt->setInt(1, static_cast<int>(menuItemType));
//             std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

//             while (res->next()) {
//                 selections.push_back(NextDayMenuVoting(
//                     res->getInt("selectionId"),
//                     res->getInt("menuItemId"),
//                     res->getInt("selectionCount"),
//                     res->getInt("sentimentScore")
//                 ));
//             }
//         } catch (sql::SQLException &e) {
//             std::cerr << "SQL error: " << e.what() << std::endl;
//         }

//         return selections;
//     }


#include "../../inc/DAO/nextDayMenuVotingDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

NextDayMenuVotingDAO::NextDayMenuVotingDAO() : databaseConnection{DatabaseConnection::getInstance()} {}

bool NextDayMenuVotingDAO::addNextDayMenuRollout(const std::vector<NextDayMenuVoting>& nextDayMenus) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("INSERT INTO NextDayMenuVoting (menuItemId, voteCount, rating, sentimentScore) VALUES (?, ?, ?, ?)"));
        
        for (const auto& menu : nextDayMenus) {
            pstmt->setInt(1, menu.menuItemId);
            pstmt->setInt(2, menu.voteCount);
            pstmt->setDouble(3, menu.rating);
            pstmt->setDouble(4, menu.sentimentScore);
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
                res->getDouble("sentimentScore")
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
            databaseConnection->getConnection()->prepareStatement("UPDATE NextDayMenuVoting SET voteCount = voteCount + 1 WHERE menuItemId = ?"));
        pstmt->setInt(1, menuItemId);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}


bool NextDayMenuVotingDAO::deleteMenuRolledOut(){
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

