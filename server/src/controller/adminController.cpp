#include "../../inc/controller/adminController.h"
#include "../../inc/serverProcess/vectorSerializer.h"
#include<iostream>
#include<vector>

AdminController::AdminController(MenuItemService* menuItemService, UserService* userService) : menuItemService(menuItemService), userService(userService){}

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
        response = "Menu Added Succesfully";
    }
    else if (operation == Operation::DeleteMenuItem) {
        bool operationDone = menuItemService->deleteMenuItemByID(std::stoi(requestData));
        std::cout<<"operationDOne deleteMenu:"<<operationDone<<std::endl;
        response = "Menu Deleted Succesfully";
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