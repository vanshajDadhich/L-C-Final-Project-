#include "../../inc/controller/adminController.h"
#include "../../inc/serverProcess/vectorSerializer.h"
#include<iostream>

AdminController::AdminController(MenuItemService* menuItemService, UserService* userService) : menuItemService(menuItemService), userService(userService){}

std::vector<std::string> AdminController::handleRequest(std::vector<std::string> request) {
    std::cout<<"Handle request in Admin Controller\n";
    std::vector<std::string> response;
    bool operationDone;
    switch (std::stoi(request[0])) {
        case Operation::AddUser:
            std::cout<<"Add User called\n";
            request.erase(request.begin());
            operationDone = userService->addUser(request);
            if(operationDone)
                response.push_back("User Added");
            else
                response.push_back("User Not Added");
            break;
        case Operation::AddMenuItem:
            request.erase(request.begin());
            operationDone = menuItemService->addMenuItem(request);
            if(operationDone)
                response.push_back("Menu Item Added");
            else
                response.push_back("Menu Item Not Added");
            break;
        case Operation::DeleteMenuItem:
            request.erase(request.begin());
            operationDone = menuItemService->deleteMenuItemByID(std::stoi(request[0]));
            if(operationDone)
                response.push_back("Menu Item Deleted");
            else
                response.push_back("Menu Item Not Deleted");
            break;
        // case Operation::UpdateMenuItem:
        //     request.erase(request.begin());
        //     menuItemService->updateMenuItem(request);
        //     break;  
        case Operation::ViewMenu:
           {
            
                VectorSerializer vectorSerializer;
                request.erase(request.begin());
                std::vector<std::vector<std::string>> menuDetails = menuItemService->getAllMenuItems(); 
                for(auto menu : menuDetails)
                {
                    std::vector<std::string> menuData;
                    for(auto data : menu)
                    {
                        menuData.push_back(data);
                    }
                    response.push_back(vectorSerializer.serialize(menuData));
                }
                break;
           }
        default:
            response.push_back("Invalid operation");
            break;
    }
    return response;
}