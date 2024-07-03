#pragma once
#include "../DTO/userProfile.h"
#include "../DAO/IUserProfileDAO.h"
#include <vector>
#include <memory>

class UserProfileService {
public:
    UserProfileService(std::shared_ptr<IUserProfileDAO> userProfileDAO);

    int addUserProfile(const UserProfile& userProfile) ;
    UserProfile getUserProfileByID(const int& userId) ;
    std::vector<UserProfile> getAllUserProfiles() ;

private:
    std::shared_ptr<IUserProfileDAO> userProfileDAO;
};
