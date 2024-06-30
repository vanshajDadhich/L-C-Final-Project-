#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include "IUserController.h"
#include "../service/menuItemService.h"
#include "../service/userService.h" 
#include "../serverProcess/vectorSerializer.h"
#include "../DAO/notificationDAO.h"
#include "../service/notificationService.h"

class AdminController : public IUserController {
    private :
        MenuItemService* menuItemService;
        UserService* userService;
        Serializable * serializer;
        NotificationService* notificationService;

    public:
        AdminController(MenuItemService* menuItemService, UserService* userService, NotificationService* notificationService);
        std::string handleRequest(Operation operation, std::string request) override;
        bool pushNotification(const MenuItem& menuItem, Operation operation);
};

#endif