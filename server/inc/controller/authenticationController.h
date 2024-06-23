#ifndef AUTHENTICATION_CONTROLLER_H
#define AUTHENTICATION_CONTROLLER_H

#include "../service/userService.h"
#include "../DTO/SerializationUtility.h"
#include "../DTO/login.h"

class AuthenticationController
{
public:
    AuthenticationController(UserService* userService);
    int authenticateUser(std::string request);
    ~AuthenticationController() = default;
private:
    UserService* userService;
};
#endif