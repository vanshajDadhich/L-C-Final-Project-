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
    this->userIdLoggedIn = login.userId;
    auto loginSerializedRequest = SerializationUtility::serializeOperation(operation, loginData);

    requestHandler->sendRequest(loginSerializedRequest);
}

void UserInterface::handleUserInput() {
    loginPrompt();
    std::string response = requestHandler->receiveResponse();
    if(response == "1"){
        std::cout<<"Admin Logged In\n";
        showMenuPrompt("1");
    }else if(response == "2"){
        std::cout<<"Chef Logged In\n";
        showMenuPrompt("2");
    }else if(response == "3"){
        std::cout<<"Employee Logged In\n";
        showMenuPrompt("3");
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
    else if(userRole == "2"){
        showChefMenu();
    }else if(userRole == "3"){
        showEmployeeMenu();
    }
}

void UserInterface::showEmployeeMenu(){
    std::cout << "Welcome Employee\n\n";
    bool flag = true;
    while (flag) {
        std::cout << "Select the operation which you like to perform\n"
                     "1. View Notification\n"
                     "2. View Chef Roll Out Menu For Tomorrow\n" 
                     "3. Select Item you want For tomorrow\n"
                     "4. Today's Menu \n"
                     "5. Provide feedback for today's Menu\n"
                     "6. Exit\n"
                     "Enter your choice: " << std::endl;

        int employeeChoice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (!(std::cin >> employeeChoice)) {
            std::cin.clear();  // clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 5: " << std::endl;
        }

        switch (employeeChoice) {
            case 1:
                viewNotification();
                break;
            case 2:
                showChefRollOutMenu();
                break;
            case 3:
                voteForTomorrowMenu();
                break;
            case 4:
                viewTodayMenu();
            case 5:
                provideFeedbackForTodayMenu();
                break;
            case 6:
                client.disconnect();
                flag = false;
                break;
            default:
                std::cout << "Invalid Choice" << std::endl;
                break;
        }
    }
}

void UserInterface::viewTodayMenu(){

}

void UserInterface::provideFeedbackForTodayMenu(){
    Operation operation = Operation::ProvideFeedback;
    Feedback feedback;
    std::cout<<"Provide Feeback "<<std::endl;
    feedback.userId = this->userIdLoggedIn;
    std::cout << "Enter Menu Item ID: ";
    std::cin >> feedback.menuItemId;
    
    std::cout << "Enter Rating: ";
    std::cin >> feedback.rating;
    
    std::cout << "Enter Comment: ";
    std::cin.ignore();  // Ignore leftover newline character from previous input
    std::getline(std::cin, feedback.comment);
    

    feedback.date = getCurrentTimestamp();

    std::string serializedData = SerializationUtility::serialize(feedback);
    std::string serializedDataForRequest = SerializationUtility::serializeOperation(operation, serializedData);

    requestHandler->sendRequest(serializedDataForRequest);
}


std::string UserInterface::getCurrentTimestamp(){
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm now_tm;
#ifdef _WIN32
    localtime_s(&now_tm, &now_time_t); // Use localtime_s on Windows
#else
    localtime_r(&now_time_t, &now_tm); // Use localtime_r on POSIX-compliant systems
#endif
    
    // Create a string stream to format the time
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    
    return oss.str();
}

void UserInterface::voteForTomorrowMenu(){
    Operation operation = Operation::VoteItemFromTomorrowMenu;
    std::cout<<"Provide MenuItem Id you want to vote for: \n";
    int menuItemId;
    std::cin>>menuItemId;
    std::string menuItemIdStr =  std::to_string(menuItemId);
    auto voteForTomorrowItemSerializedRequest = SerializationUtility::serializeOperation(operation,menuItemIdStr);
    requestHandler->sendRequest(voteForTomorrowItemSerializedRequest);
}



void UserInterface::showChefRollOutMenu(){
    Operation operation = Operation::GetChefRollOutMenuForTomorrow;
    std::string viewMenuSerializedRequest = SerializationUtility::serializeOperation(operation, "");
    requestHandler->sendRequest(viewMenuSerializedRequest);

    std::string serializedMenuList = requestHandler->receiveResponse();

     std::vector<std::string>MenuList = VectorSerializer::deserialize(serializedMenuList);

    for (const auto& item : MenuList) {
        auto menuItem = SerializationUtility::deserialize<NextDayMenuRollOut>(item);

        std::cout << "Menu Item Details:" << std::endl
          << "Menu Item ID: " << menuItem.menuItemId << "\t"
          << "Menu Item Name: " << menuItem.menuItemName << "\t"
          << "Menu Item Type: " << static_cast<int>(menuItem.menuItemType) << "\t"
          << "Price: " << menuItem.price << "\t"
          << "Average Rating: " << menuItem.averageRating << "\t"
          << "Sentiment Score: " << menuItem.sentimentScore << std::endl;
    }
}

void UserInterface::viewNotification(){

}

void UserInterface::showChefMenu(){
    std::cout << "Welcome Chef\n\n";
    bool flag = true;
    while (flag) {
        std::cout << "Select the operation which you like to perform\n"
                     "1. View Menu\n"
                     "2. Get Recommendation Menu\n"
                     "3. Roll out Menu For Tomorrow\n"
                     "4. Publish Menu For Today\n"
                     "5. Exit\n"
                     "Enter your choice: " << std::endl;

        int chefChoice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (!(std::cin >> chefChoice)) {
            std::cin.clear();  // clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 5: " << std::endl;
        }

        switch (chefChoice) {
            case 1:
                showMenu();
                break;
            case 2:
                selectMealTypeForRecommendationMenu();
                break;
            case 3:
                rollOutMenuForTomorrow();
                break;
            case 4:
                publishMenuForToday();
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
}

void UserInterface::rollOutMenuForTomorrow(){
    Operation operation = Operation::RollOutMenuForNextDay;
    std::cout<<"Roll out Menu For Tomorrow (choose MenuItem Id from Recommended Items)\n"
             <<"Select MenuItemID for BreakFast seprated by comma \n";
    
    std::vector<std::string> chefRollOutMenuForTomorrow;
    std::string menuItemIdsforBreakfast;
    std::cin>>menuItemIdsforBreakfast;
    chefRollOutMenuForTomorrow.push_back(menuItemIdsforBreakfast);
    
    std::cout<<"Select MenuItemID for Lunch seprated by comma \n";
    std::string menuItemIdsforLunch;
    std::cin>>menuItemIdsforLunch;
    chefRollOutMenuForTomorrow.push_back(menuItemIdsforLunch);

    std::cout<<"Select MenuItemID for Dinner seprated by comma \n";
    std::string menuItemIdsforDinner;
    std::cin>>menuItemIdsforDinner;
    chefRollOutMenuForTomorrow.push_back(menuItemIdsforDinner);

    std::string serializeRequestData = VectorSerializer::serialize(chefRollOutMenuForTomorrow);

    std::string serializedRequestWithOperation = SerializationUtility::serializeOperation(operation, serializeRequestData);
    std::cout<<"Roll Out Menu Serialized Data"<<serializedRequestWithOperation<<std::endl;
    requestHandler->sendRequest(serializedRequestWithOperation);
}

void UserInterface::publishMenuForToday(){
    std::cout<<"publishMenuForToday";
}


void UserInterface::selectMealTypeForRecommendationMenu(){
    bool flag = true;
    while (flag) {
        std::cout << "Select the MealType you would like to get Recommendation For\n"
                    "1. BreakFast\n"
                    "2. Lunch\n"
                    "3. Dinner\n"
                    "4. Exit\n"
                    "Enter your choice: " << std::endl;

        int recommendationMealTypeChoice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (!(std::cin >> recommendationMealTypeChoice)) {
            std::cin.clear();  // clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 5: " << std::endl;
        }

        if(recommendationMealTypeChoice > 0 && recommendationMealTypeChoice < 4){
           MenuItemType menuItemType = static_cast<MenuItemType>(recommendationMealTypeChoice);
           showRecommendedMenu(menuItemType);
        }else if(recommendationMealTypeChoice == 4){
            flag = false;
        }else{
            std::cout << "Invalid Choice" << std::endl;
        }
    }
}

void UserInterface::showRecommendedMenu(MenuItemType menuItemType){
    std::cout<<"Inside Show Recommended Menu\n";
    Operation operation = Operation::GetRecommandationFromEngine;
    std::string mealtype = std::to_string(menuItemType);
    std::string viewMenuSerializedRequest = SerializationUtility::serializeOperation(operation, mealtype);
    requestHandler->sendRequest(viewMenuSerializedRequest);

    std::string serializedMenuList = requestHandler->receiveResponse();

    std::vector<std::string>MenuList = VectorSerializer::deserialize(serializedMenuList);

    for (const auto& item : MenuList) {
        auto menuItem = SerializationUtility::deserialize<NextDayMenuRollOut>(item);

        std::cout << "Menu Item Details:" << std::endl
          << "Menu Item ID: " << menuItem.menuItemId << "\t"
          << "Menu Item Name: " << menuItem.menuItemName << "\t"
          << "Menu Item Type: " << static_cast<int>(menuItem.menuItemType) << "\t"
          << "Price: " << menuItem.price << "\t"
          << "Average Rating: " << menuItem.averageRating << "\t"
          << "Sentiment Score: " << menuItem.sentimentScore << std::endl;
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

    std::cout<<"serializedMenuList"<<serializedMenuList<<std::endl;

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
