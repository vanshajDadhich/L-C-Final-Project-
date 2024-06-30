#include "../../inc/controller/adminController.h"
#include "../../inc/serverProcess/vectorSerializer.h"
#include<iostream>
#include<vector>

AdminController::AdminController(MenuItemService* menuItemService, UserService* userService, NotificationService* notificationService) 
            : menuItemService(menuItemService), userService(userService), notificationService(notificationService){}

std::string AdminController::handleRequest(Operation operation, std::string requestData) {
    std::cout<<"Handle request in Admin Controller\n";
    std::string response;
    if (operation == Operation::AddUser) {
        std::cout << "Add User called\n";
        User user = SerializationUtility::deserialize<User>(requestData);
        int operationDone = userService->addUser(user);   
        std::cout<<"operationDOne add user:"<<operationDone<<std::endl;
        response = "User Added Succesfully";
    }
    else if (operation == Operation::AddMenuItem) {
        std::cout<<"Add Menu Item Called\n";
        MenuItem menuItem = SerializationUtility::deserialize<MenuItem>(requestData);
        bool operationDone = menuItemService->addMenuItem(menuItem);
        std::cout<<"operationDone add Menu:"<<operationDone<<std::endl;
        response = "Menu Item Added Succesfully";
        pushNotification(menuItem, Operation::AddMenuItem);
    }
    else if (operation == Operation::DeleteMenuItem) {
        MenuItem menuItem = menuItemService->deleteMenuItemByID(std::stoi(requestData));
        response = "Menu Item Deleted Succesfully";
        pushNotification(menuItem, Operation::DeleteMenuItem);
    }
    else if (operation == Operation::ViewMenu) {
        std::vector<MenuItem> menuDetails = menuItemService->getAllMenuItems();
        std::vector<std::string> menuSerializedData;
        for (auto menu : menuDetails) {
            menuSerializedData.push_back(SerializationUtility::serialize(menu));
        }
        response = VectorSerializer::serialize(menuSerializedData);
        std::cout<<"operationDOne : view menu data send"<<std::endl;
    }
    else {
        response = "Invalid operation";
    }
    return response;
}

bool AdminController::pushNotification(const MenuItem& menuItem, Operation operation) {
    Notification notification;
    std::string  menuType = menuItem.menuItemType == 1 ? "Breakfast" : menuItem.menuItemType == 2 ? "Lunch" : "Dinner";
    if(Operation::AddMenuItem == operation) {
       notification.notificationTitle = "New Menu Item Added";
       notification.message = menuItem.menuItemName + " has been added to the menu" + " with price " + std::to_string(menuItem.price) + " and type " + menuType;
    }else {
        notification.notificationTitle = "Menu Item Deleted";
        notification.message = menuItem.menuItemName + " has been deleted from the menu";
    }

    return notificationService->addNotification(notification);
}