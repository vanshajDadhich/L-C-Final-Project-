#include "../../inc/controller/authenticationController.h"
#include<iostream>

AuthenticationController::AuthenticationController(UserService* userService)
    : userService(userService) {}

int AuthenticationController::authenticateUser(const int& userId, const std::string& password) {
    std::cout<<"Authenticating User : 8\n";
    return userService->authenticateUser(userId, password);
}
