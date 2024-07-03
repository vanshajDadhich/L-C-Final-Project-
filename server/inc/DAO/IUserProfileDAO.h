#pragma once
#include "databaseConnection.h"
#include "../DTO/userProfile.h"
#include <vector>
#include <memory>

class IUserProfileDAO {
public:
    virtual ~IUserProfileDAO() = default;

    virtual int addUserProfile(const UserProfile& userProfile) = 0;
    virtual UserProfile getUserProfileByID(const int& userId) = 0;
    virtual std::vector<UserProfile> getAllUserProfiles() = 0;
};
