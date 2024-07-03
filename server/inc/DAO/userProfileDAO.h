#pragma once
#include "databaseConnection.h"
#include "IUserProfileDAO.h"
#include <vector>

class UserProfileDAO : public IUserProfileDAO {
public:
    UserProfileDAO();

    int addUserProfile(const UserProfile& userProfile) override;
    UserProfile getUserProfileByID(const int& userId) override;
    std::vector<UserProfile> getAllUserProfiles() override;

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};
