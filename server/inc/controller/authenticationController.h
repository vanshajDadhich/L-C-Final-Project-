#ifndef AUTHENTICATION_CONTROLLER_H
#define AUTHENTICATION_CONTROLLER_H

#include "../service/userService.h"
#include "../DTO/serializationUtility.h"
#include "../DTO/login.h"
#include <memory>

class AuthenticationController {
public:
    explicit AuthenticationController(std::unique_ptr<UserService> userService);
    int authenticateUser(const std::string& requestData);
    ~AuthenticationController() = default;

private:
    std::unique_ptr<UserService> userService;

    bool isValidLogin(const Login& loginCredentials, const User& user) const;
};

#endif
