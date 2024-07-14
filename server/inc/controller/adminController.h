#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include <memory>
#include <vector>
#include "IUserController.h"

class AdminController : public IUserController {
public:
    AdminController(std::unique_ptr<MenuItemService> menuItemService, 
                    std::unique_ptr<UserService> userService, 
                    std::unique_ptr<NotificationService> notificationService);

    std::string handleRequest(Operation operation, const std::string& request) override;

private:
    std::unique_ptr<MenuItemService> menuItemService;
    std::unique_ptr<UserService> userService;
    std::unique_ptr<NotificationService> notificationService;

    std::string handleAddUser(const std::string& requestData);
    std::string handleAddMenuItem(const std::string& requestData);
    std::string handleDeleteMenuItem(const std::string& requestData);
    std::string handleViewMenu(const std::string& requestData);
    std::string handleUpdateMenuItem(const std::string& requestData);
    std::string handleGetMenuItemById(const std::string& requestData);
    bool pushNotification(const MenuItem& menuItem, Operation operation);
};

#endif
