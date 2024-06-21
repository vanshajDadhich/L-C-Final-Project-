#include "../inc/userInterface.h"
#include <iostream>
#include <limits> 
#include<vector>


UserInterface::UserInterface(Client& client)
    : client(client), requestHandler(nullptr) {}

void UserInterface::run() {
    if (!client.connectToServer()) {
        std::cerr << "Failed to connect to server" << std::endl;
        return;
    }

    requestHandler = new RequestHandler(client.getSocket(), client.getAddress());
    handleUserInput();

    delete requestHandler;
    client.disconnect();
}

void UserInterface::loginPrompt()
{
    int userId;
    std::string password;
    std::cout << "Enter Login Credantials: \n";
    std::cout<<"UserId : ";
    std::cin>>userId;
    std::cout<<"Password : ";
    std::cin>>password;
    int operation = Operation::login;

    requestHandler->sendRequest({std::to_string(operation), std::to_string(userId), password} ) ;
}

void UserInterface::handleUserInput() {
    loginPrompt();
    std::vector<std::string> response = requestHandler->receiveResponse();
    if(response[0] == "1"){
        std::cout<<"Admin Logged In\n";
        showMenuPrompt("1");
    }else if(response[0] == "2"){
        std::cout<<"Chef Logged In\n";
    }else if(response[0] == "3"){
        std::cout<<"Employee Logged In\n";
    }else{
        std::cout<<"Invalid Login\n";
    }
}

void UserInterface::showMenuPrompt(std::string userRole)
{
    if (userRole == "1")
    {
        showAdminMenu();
    }
}
int UserInterface::showAdminMenu()
{
     std::cout << "Welcome Admin\n\n";
    bool flag = true;
    while (flag) {
        std::cout << "Select the operation which you like to perform\n"
                     "1. Add menu Item\n"
                     "2. Delete Menu Item\n"
                     "3. View Menu\n"
                     "4. Add User\n"
                     "5. Exit\n"
                     "Enter your choice: " << std::endl;

        int adminChoice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (!(std::cin >> adminChoice)) {
            std::cin.clear();  // clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 5: " << std::endl;
        }

        switch (adminChoice) {
            case 1:
                showAddItemPrompt();
                break;
            case 2:
                showDeleteItemPrompt();
                break;
            case 3:
                showMenu();
                break;
            case 4:
                addUserPrompt();
                break;
            case 5:
                client.disconnect();
                flag = false;
                break;
            default:
                std::cout << "Invalid Choice" << std::endl;
                break;
        }
    }
    return 0;
}

void UserInterface::addUserPrompt() {
    std::vector<std::string> userResponse;
    userResponse.push_back(std::to_string(Operation::AddUser));
    
    std::string userName, userRole, userPassword;

    std::cout << "Enter User name: " << std::endl;
    std::getline(std::cin >> std::ws, userName);
    userResponse.push_back(userName);

    std::cout << "Enter User password: " << std::endl;
    std::getline(std::cin >> std::ws, userPassword);
    userResponse.push_back(userPassword);

     std::cout << "Enter User role: " << std::endl;
    std::getline(std::cin >> std::ws, userRole);
    userResponse.push_back(userRole);


    std::cout << "Sending addUser request to server\n";
    requestHandler->sendRequest(userResponse);
}

void UserInterface::showAddItemPrompt() {
    std::vector<std::string> userResponse;
    userResponse.push_back(std::to_string(Operation::AddMenuItem));
    
    std::string itemName, itemPrice, itemAvailability, mealType;

    std::cout << "Enter Item name: " << std::endl;
    std::getline(std::cin >> std::ws, itemName);
    userResponse.push_back(itemName);

    std::cout << "Enter Item price: " << std::endl;
    std::getline(std::cin >> std::ws, itemPrice);
    userResponse.push_back(itemPrice);

    std::cout << "Enter Item availability: " << std::endl;
    std::getline(std::cin >> std::ws, itemAvailability);
    userResponse.push_back(itemAvailability);

    std::cout << "Enter meal type (breakfast/lunch/dinner): " << std::endl;
    std::getline(std::cin >> std::ws, mealType);
    userResponse.push_back(mealType);

    std::cout << "Sending addItem request to server\n";
    requestHandler->sendRequest(userResponse);
}


void UserInterface::showDeleteItemPrompt() {
    std::string itemName;
    std::vector<std::string> userResponse{std::to_string(Operation::DeleteMenuItem)};

    std::cout << "Enter the name of item to delete: " << std::endl;
    std::getline(std::cin >> std::ws, itemName);
    userResponse.push_back(itemName);

    requestHandler->sendRequest(userResponse);
}


void UserInterface::showMenu() {
    std::vector<std::string> userResponse{std::to_string(Operation::ViewMenu)};
    requestHandler->sendRequest(userResponse);

    VectorSerializer vectorSerializer;
    std::vector<std::string> menu = requestHandler->receiveResponse();

    for (const auto& item : menu) {
        auto menuItemData = vectorSerializer.deserialize(item);
        for (const auto& field : menuItemData) {
            std::cout << field << " , ";
        }
        std::cout << std::endl;
    }
}
