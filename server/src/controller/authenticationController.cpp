#include "../../inc/controller/authenticationController.h"
#include <iostream>

AuthenticationController::AuthenticationController(std::unique_ptr<UserService> userService)
    : userService(std::move(userService)) {}

int AuthenticationController::authenticateUser(const std::string& requestData) {
    int userRole = -1;
    Login loginCredentials = SerializationUtility::deserialize<Login>(requestData);
    User user = userService->getUserById(loginCredentials.userId);

    if (isValidLogin(loginCredentials, user)) {
        std::cout << "[AuthenticationController] User authenticated successfully. UserID: " << loginCredentials.userId << "\n";
        userRole =  user.role;
    }

    return userRole;
}

bool AuthenticationController::isValidLogin(const Login& loginCredentials, const User& user) const {
    return user.userId == loginCredentials.userId && user.password == loginCredentials.password;
}
