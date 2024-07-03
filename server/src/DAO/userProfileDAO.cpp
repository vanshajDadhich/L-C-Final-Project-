#include "../../inc/DAO/userProfileDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

UserProfileDAO::UserProfileDAO() : databaseConnection{DatabaseConnection::getInstance()} {}

int UserProfileDAO::addUserProfile(const UserProfile& userProfile) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("INSERT INTO UserProfile (userId, vegetarianPreference, spiceLevelOption, foodPreference, sweetToothPreference) VALUES (?, ?, ?, ?, ?)"));
        pstmt->setInt(1, userProfile.userId);
        pstmt->setInt(2, static_cast<int>(userProfile.vegetarianPreference));
        pstmt->setInt(3, static_cast<int>(userProfile.spiceLevelOption));
        pstmt->setInt(4, static_cast<int>(userProfile.foodPreference));
        pstmt->setInt(5, static_cast<int>(userProfile.sweetToothPreference));
        int updateCount = pstmt->executeUpdate();

        // Check if the update was successful
        if (updateCount == 0) {
            std::cerr << "Failed to add user profile." << std::endl;
            return -1; // Return -1 on failure
        }

        return userProfile.userId;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return -1; // Return -1 on error
    }
}

UserProfile UserProfileDAO::getUserProfileByID(const int& userId) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement("SELECT * FROM UserProfile WHERE userId = ?"));
        pstmt->setInt(1, userId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            return UserProfile(
                res->getInt("userId"),
                static_cast<VegetarianPreference>(res->getInt("vegetarianPreference")),
                static_cast<SpiceLevelOption>(res->getInt("spiceLevelOption")),
                static_cast<FoodPreference>(res->getInt("foodPreference")),
                static_cast<SweetToothPreference>(res->getInt("sweetToothPreference"))
            );
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    // Return a default-constructed UserProfile if not found or error
    return UserProfile();
}

std::vector<UserProfile> UserProfileDAO::getAllUserProfiles() {
    std::vector<UserProfile> userProfiles;

    try {
        std::unique_ptr<sql::Statement> stmt(databaseConnection->getConnection()->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM UserProfile"));

        while (res->next()) {
            userProfiles.push_back(UserProfile(
                res->getInt("userId"),
                static_cast<VegetarianPreference>(res->getInt("vegetarianPreference")),
                static_cast<SpiceLevelOption>(res->getInt("spiceLevelOption")),
                static_cast<FoodPreference>(res->getInt("foodPreference")),
                static_cast<SweetToothPreference>(res->getInt("sweetToothPreference"))
            ));
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return userProfiles;
}
