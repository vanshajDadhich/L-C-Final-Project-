#ifndef USER_PROFILE_SERVICE_H
#define USER_PROFILE_SERVICE_H

#include "../DTO/userProfile.h"
#include "../DAO/IUserProfileDAO.h"
#include <vector>
#include <memory>

class UserProfileService {
public:
    UserProfileService(std::unique_ptr<IUserProfileDAO> userProfileDAO);

    int addUserProfile(const UserProfile& userProfile) ;
    UserProfile getUserProfileByID(const int& userId) ;
    std::vector<UserProfile> getAllUserProfiles() ;

private:
    std::unique_ptr<IUserProfileDAO> userProfileDAO;
};

#endif