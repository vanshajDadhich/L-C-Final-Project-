#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H

#include <string>
#include <memory>
#include <iostream>
#include "../controller/authenticationController.h"
#include "../controller/IUserController.h"

class RequestProcessor {
private:
    std::unique_ptr<AuthenticationController> authenticationController;
    std::unique_ptr<IUserController> userController;

    std::unique_ptr<IUserController> initializeAdminController();
    std::unique_ptr<IUserController> initializeEmployeeController();
    std::unique_ptr<IUserController> initializeChefController();
    std::string handleLoginRequest(const std::string& requestData);
    std::string handleUserRequest(Operation operation, const std::string& requestData);

public:
    RequestProcessor();
    std::string processRequest(const std::string& request);
};

#endif
