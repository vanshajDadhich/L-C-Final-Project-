#include "../../inc/DAO/userProfileDAO.h"
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <iostream>

UserProfileDAO::UserProfileDAO() : databaseConnection{DatabaseConnection::getInstance()} {}

bool UserProfileDAO::addUserProfile(const UserProfile& userProfile) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement(
                "INSERT INTO UserProfile (userId, vegetarianPreference, spiceLevelOption, cuisinePreference, sweetToothPreference) VALUES (?, ?, ?, ?, ?)"));
        pstmt->setInt(1, userProfile.userId);
        pstmt->setInt(2, static_cast<int>(userProfile.vegetarianPreference));
        pstmt->setInt(3, static_cast<int>(userProfile.spiceLevelOption));
        pstmt->setInt(4, static_cast<int>(userProfile.cuisinePreference));
        pstmt->setInt(5, static_cast<int>(userProfile.sweetToothPreference));
        int updateCount = pstmt->executeUpdate();

        if (updateCount == 0) {
            std::cerr << "Failed to add user profile." << std::endl;
            return false;
        }

        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
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
                static_cast<CuisinePreference>(res->getInt("cuisinePreference")),
                static_cast<SweetToothPreference>(res->getInt("sweetToothPreference"))
            );
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

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
                static_cast<CuisinePreference>(res->getInt("cuisinePreference")),
                static_cast<SweetToothPreference>(res->getInt("sweetToothPreference"))
            ));
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }

    return userProfiles;
}

bool UserProfileDAO::updateUserProfile(const UserProfile& userProfile) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            databaseConnection->getConnection()->prepareStatement(
                "UPDATE UserProfile SET vegetarianPreference = ?, spiceLevelOption = ?, cuisinePreference = ?, sweetToothPreference = ? WHERE userId = ?"));
        pstmt->setInt(1, static_cast<int>(userProfile.vegetarianPreference));
        pstmt->setInt(2, static_cast<int>(userProfile.spiceLevelOption));
        pstmt->setInt(3, static_cast<int>(userProfile.cuisinePreference));
        pstmt->setInt(4, static_cast<int>(userProfile.sweetToothPreference));
        pstmt->setInt(5, userProfile.userId);
        int updateCount = pstmt->executeUpdate();

        if (updateCount == 0) {
            return addUserProfile(userProfile);
        }

        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return false;
    }
}
