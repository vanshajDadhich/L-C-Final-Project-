#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include "IUserController.h"
#include "../service/menuItemService.h"
#include "../service/userService.h" 
#include "../serverProcess/vectorSerializer.h"

class AdminController : public IUserController {
    private :
        MenuItemService* menuItemService;
        UserService* userService;
        Serializable * serializer;

    public:
        AdminController(MenuItemService* menuItemService, UserService* userService);
        std::string handleRequest(Operation operation, std::string request) override;
        int addUser(const User& user);
};

#endif