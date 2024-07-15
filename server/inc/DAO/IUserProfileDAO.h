#pragma once
#include "databaseConnection.h"
#include "../../../common/DTO/userProfile.h"
#include <vector>
#include <memory>

class IUserProfileDAO {
public:
    virtual ~IUserProfileDAO() = default;

    virtual bool addUserProfile(const UserProfile& userProfile) = 0;
    virtual UserProfile getUserProfileByID(const int& userId) = 0;
    virtual std::vector<UserProfile> getAllUserProfiles() = 0;
    virtual bool updateUserProfile(const UserProfile& userProfile) = 0;
};
