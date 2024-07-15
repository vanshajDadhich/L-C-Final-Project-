#include "../../inc/controller/adminController.h"
#include <iostream>

AdminController::AdminController(std::unique_ptr<MenuItemService> menuItemService, std::unique_ptr<UserService> userService, std::unique_ptr<NotificationService> notificationService)
    : menuItemService(std::move(menuItemService)), userService(std::move(userService)), notificationService(std::move(notificationService)) {}

std::string AdminController::handleRequest(Operation operation, const std::string& requestData) {
    std::cout << "[AdminController] Handling request: " << static_cast<int>(operation) << "\n";
    std::string response;

    if (operation == Operation::AddUser) {
        response = handleAddUser(requestData);
    } else if (operation == Operation::AddMenuItem) {
        response = handleAddMenuItem(requestData);
    } else if (operation == Operation::DeleteMenuItem) {
        response = handleDeleteMenuItem(requestData);
    } else if (operation == Operation::ViewMenu) {
        response = handleViewMenu(requestData);
    } else if (operation == Operation::UpdateMenuItem) {
        response = handleUpdateMenuItem(requestData);
    } else if (operation == Operation::GetMenuItemById) {
        response = handleGetMenuItemById(requestData);
    } else {
        std::cerr << "[AdminController] Invalid operation: " << static_cast<int>(operation) << "\n";
        response = "Invalid operation";
    }
    return response;
}

std::string AdminController::handleGetMenuItemById(const std::string& requestData) {
    std::string response;
    int menuItemId;
    try {
        menuItemId = std::stoi(requestData);
    } catch (const std::invalid_argument&) {
        std::cerr << "[AdminController] Invalid menu item ID\n";
        response = "Invalid menu item ID";
    }
    MenuItem menuItem = menuItemService->getMenuItemById(menuItemId);
    std::cout << "[AdminController] Get Menu Item By ID operation completed\n";
    if (menuItem.menuItemId != 0) {
        response = SerializationUtility::serialize(menuItem);
    } else {
        response = "Menu Item Not Found";
    }
    return response;
}

std::string AdminController::handleUpdateMenuItem(const std::string& requestData) {
    std::string response;
    std::cout << "[AdminController] Update Menu Item called\n";
    MenuItem menuItem = SerializationUtility::deserialize<MenuItem>(requestData);
    bool operationDone = menuItemService->updateMenuItem(menuItem);
    std::cout << "[AdminController] Update Menu Item operation completed with result: " << operationDone << "\n";
    if (operationDone) {
        pushNotification(menuItem, Operation::UpdateMenuItem);
        response = "Menu Item Updated Successfully";
    } else {
        response = "Menu Item Not Updated";
    }
    return response;
}

std::string AdminController::handleAddUser(const std::string& requestData) {
    std::string response = "";
    std::cout << "[AdminController] Add User called\n";
    User user = SerializationUtility::deserialize<User>(requestData);
    int operationDone = userService->addUser(user);
    std::cout << "[AdminController] Add User operation completed with result: " << operationDone << "\n";
    if (operationDone) {
        response =  "User Added Successfully";
    } else {
        response =  "User Not Added";
    }
    return response;
}

std::string AdminController::handleAddMenuItem(const std::string& requestData) {
    std::string response;
    std::cout << "[AdminController] Add Menu Item called\n";
    MenuItem menuItem = SerializationUtility::deserialize<MenuItem>(requestData);
    bool operationDone = menuItemService->addMenuItem(menuItem);
    std::cout << "[AdminController] Add Menu Item operation completed with result: " << operationDone << "\n";
    if (operationDone) {
        pushNotification(menuItem, Operation::AddMenuItem);
        response = "Menu Item Added Successfully";
    } else {
        response = "Menu Item Not Added";
    }
    return response;
}

std::string AdminController::handleDeleteMenuItem(const std::string& requestData) {
    std::string response;
    int menuItemId;
    try {
        menuItemId = std::stoi(requestData);
    } catch (const std::invalid_argument&) {
        std::cerr << "[AdminController] Invalid menu item ID\n";
        response = "Invalid menu item ID";
    }
    std::cout << "[AdminController] Delete Menu Item called\n";
    MenuItem menuItem = menuItemService->deleteMenuItemById(menuItemId);
    std::cout << "[AdminController] Delete Menu Item operation completed\n";
    if (menuItem.menuItemId != 0) {
        pushNotification(menuItem, Operation::DeleteMenuItem);
        response = "Menu Item Deleted Successfully";
    } else {
        response = "Menu Item Not Deleted";
    }
    return response;
}

std::string AdminController::handleViewMenu(const std::string& requestData) {
    std::cout << "[AdminController] View Menu called\n";
    std::vector<MenuItem> menuDetails = menuItemService->getAllMenuItems();
    std::vector<std::string> menuSerializedData;
    for (const auto& menu : menuDetails) {
        menuSerializedData.push_back(SerializationUtility::serialize(menu));
    }
    std::cout << "[AdminController] View Menu operation completed\n";
    return SerializationUtility::serializeStringVector(menuSerializedData);
}

bool AdminController::pushNotification(const MenuItem& menuItem, Operation operation) {
    Notification notification;
    std::string menuType = menuItem.menuItemType == 1 ? "Breakfast" :
                            menuItem.menuItemType == 2 ? "Lunch" : "Dinner";

    if (Operation::AddMenuItem == operation) {
        notification.notificationTitle = "New Menu Item Added";
        notification.message = "Menu Item: " + menuItem.menuItemName + " (ID: " + std::to_string(menuItem.menuItemId) + ") has been added to the menu. Price: " + std::to_string(menuItem.price) + ", Type: " + menuType;
    } else {
        notification.notificationTitle = "Menu Item Deleted";
        notification.message = "Menu Item: " + menuItem.menuItemName + " (ID: " + std::to_string(menuItem.menuItemId) + ") has been deleted from the menu.";
    }

    std::cout << "[AdminController] Pushing notification: " << notification.notificationTitle << " - " << notification.message << "\n";
    return notificationService->addNotification(notification);
}
