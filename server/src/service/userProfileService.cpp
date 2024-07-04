#include "../../inc/service/userProfileService.h"

UserProfileService::UserProfileService(std::unique_ptr<IUserProfileDAO> userProfileDAO)
    : userProfileDAO(std::move(userProfileDAO)) {}

int UserProfileService::addUserProfile(const UserProfile& userProfile) {
    return userProfileDAO->addUserProfile(userProfile);
}

UserProfile UserProfileService::getUserProfileByID(const int& userId) {
    return userProfileDAO->getUserProfileByID(userId);
}

std::vector<UserProfile> UserProfileService::getAllUserProfiles() {
    return userProfileDAO->getAllUserProfiles();
}
