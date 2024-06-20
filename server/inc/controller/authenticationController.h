#ifndef AUTHENTICATION_CONTROLLER_H
#define AUTHENTICATION_CONTROLLER_H

#include "../service/userService.h"

class AuthenticationController
{
public:
    AuthenticationController(UserService* userService);
    bool authenticateUser(const int& userId, const std::string& password);
    ~AuthenticationController() = default;
private:
    UserService* userService;
};
#endif 