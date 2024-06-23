#include "../../inc/controller/authenticationController.h"
#include<iostream>

AuthenticationController::AuthenticationController(UserService* userService)
    : userService(userService) {}

int AuthenticationController::authenticateUser(std::string request) {
    Login loginData = SerializationUtility::deserialize<Login>(request);
    std::cout<<"Authenticating User : 8\n";
    return userService->authenticateUser(loginData.userId, loginData.password);
}
