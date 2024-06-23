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
    Login login;
    std::cout << "Enter Login Credantials: \n";
    std::cout<<"UserId : ";
    std::cin>>login.userId;
    std::cout<<"Password : ";
    std::cin>>login.password;
    Operation operation = Operation::login;
    auto loginData = SerializationUtility::serialize(login);
    auto loginSerializedRequest = SerializationUtility::serializeOperation(operation, loginData);

    requestHandler->sendRequest(loginSerializedRequest) ;
}

void UserInterface::handleUserInput() {
    loginPrompt();
    std::string response = requestHandler->receiveResponse();
    if(response == "1"){
        std::cout<<"Admin Logged In\n";
        showMenuPrompt("1");
    }else if(response == "2"){
        std::cout<<"Chef Logged In\n";
    }else if(response == "3"){
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
    User user;
    Operation operation = Operation::AddUser;

    std::cout << "Enter User name: " << std::endl;
    std::getline(std::cin >> std::ws, user.name);

    std::cout << "Enter User password: " << std::endl;
    std::getline(std::cin >> std::ws, user.password);

    int roleInt;
    std::cout << "Enter Role (1 for Admin, 2 for Chef, 3 for Employee): ";
    std::cin >> roleInt;
    if (roleInt == 1) {
        user.role = Admin;
    } else if (roleInt == 2) {
        user.role = Chef;
    } else if (roleInt == 3) {
        user.role = Employee;
    } else {
        std::cerr << "Invalid role entered!" << std::endl;
    }
    auto userData = SerializationUtility::serialize(user);
    auto addUserSerializedRequest = SerializationUtility::serializeOperation(operation, userData);
    requestHandler->sendRequest(addUserSerializedRequest);
}

void UserInterface::showAddItemPrompt() {
    Operation operation = Operation::AddMenuItem;
    std::string menuItemName;
    int menuItemTypeInt;
    bool availability;
    int price;

    std::cout << "Enter Item name: " << std::endl;
    std::getline(std::cin >> std::ws, menuItemName);

    std::cout << "Enter Item price: " << std::endl;
    std::cin>>price;

    std::cout << "Enter Item availability: " << std::endl;
    std::cin>>availability;

    std::cout << "Enter meal type (1 for Breakfast, 2 for Lunch, 3 for Dinner): "<<std::endl;
    std::cin>>menuItemTypeInt;
    
    MenuItem menuItem(0, menuItemName, menuItemTypeInt, availability, price);
    auto menuItemData = SerializationUtility::serialize(menuItem);
    auto addMenuSerializedRequest = SerializationUtility::serializeOperation(operation, menuItemData);

    std::cout << "Sending addItem request to server\n";
    requestHandler->sendRequest(addMenuSerializedRequest);
}


void UserInterface::showDeleteItemPrompt() {
    int menuItemId;
    Operation operation = Operation::DeleteMenuItem;

    std::cout << "Enter the Id of menu item to delete: " << std::endl;
    std::cin>>menuItemId;
    std::string menuItemIdStr =  std::to_string(menuItemId);
    auto deleteMenuItemSerializedRequest = SerializationUtility::serializeOperation(operation,menuItemIdStr);

    requestHandler->sendRequest(deleteMenuItemSerializedRequest);
}


void UserInterface::showMenu() {
    std::cout<<"Inside Show Menu\n";
    Operation operation = Operation::ViewMenu;
    std::string viewMenuSerializedRequest = SerializationUtility::serializeOperation(operation, "");
    requestHandler->sendRequest(viewMenuSerializedRequest);

    std::string serializedMenuList = requestHandler->receiveResponse();

    std::vector<std::string>MenuList = VectorSerializer::deserialize(serializedMenuList);

    for (const auto& item : MenuList) {
        auto menuItem = SerializationUtility::deserialize<MenuItem>(item);

        std::cout << "Menu Item Details:" << std::endl
          << "ID: " << menuItem.menuItemId << std::endl
          << "Name: " << menuItem.menuItemName << std::endl
          << "Type: " << static_cast<int>(menuItem.menuItemType) << std::endl  // Assuming you want to print the enum as an integer
          << "Availability: " << (menuItem.availability ? "Yes" : "No") << std::endl
          << "Price: " << menuItem.price << std::endl;
        std::cout << std::endl;
    }
}
