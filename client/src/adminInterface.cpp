#include "../inc/adminInterface.h"
#include <iostream>
#include <limits>
#include <vector>

AdminInterface::AdminInterface(RequestHandler* requestHandler) : requestHandler(requestHandler) {}

void AdminInterface::showMenu()
{
    std::cout << "Welcome Admin\n\n";
    bool flag = true;
    while (flag) {
        std::cout << "Select the operation you would like to perform:\n"
                     "1. Add menu item\n"
                     "2. Delete menu item\n"
                     "3. View menu\n"
                     "4. Add user\n"
                     "5. Exit\n"
                     "Enter your choice: " << std::endl;

        int adminChoice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (!(std::cin >> adminChoice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                showMenuItemList();
                break;
            case 4:
                addUserPrompt();
                break;
            case 5:
                flag = false;
                break;
            default:
                std::cout << "Invalid Choice" << std::endl;
                break;
        }
    }
}


void AdminInterface::showAddItemPrompt() {
    Operation operation = Operation::AddMenuItem;
    MenuItem menuItem;
    int menuItemTypeInt;
    int vegetarianPreferenceInt;
    int spiceLevelOptionInt;
    int foodPreferenceInt;
    int sweetToothPreferenceInt;

    std::cout << "Enter Item name: " << std::endl;
    std::getline(std::cin >> std::ws, menuItem.menuItemName);

    std::cout << "Enter Item price:" << std::endl;
    std::cin >> menuItem.price;

    std::cout << "Enter Item availability: (0 for not available and 1 for available )" << std::endl;
    std::cin >> menuItem.availability;

    std::cout << "Enter meal type (1 for Breakfast, 2 for Lunch, 3 for Dinner): " << std::endl;
    std::cin >> menuItemTypeInt;
    menuItem.menuItemType = static_cast<MenuItemType>(menuItemTypeInt);

    // Additional fields
    std::cout << "Enter vegetarian preference (1 for Vegetarian, 2 for Non Vegetarian, 3 for Eggetarian): " << std::endl;
    std::cin >> vegetarianPreferenceInt;
    menuItem.vegetarianPreference = static_cast<VegetarianPreference>(vegetarianPreferenceInt);

    std::cout << "Enter spice level option (1 for High, 2 for Medium, 3 for Low): " << std::endl;
    std::cin >> spiceLevelOptionInt;
    menuItem.spiceLevelOption = static_cast<SpiceLevelOption>(spiceLevelOptionInt);

    std::cout << "Enter food preference (1 for North Indian, 2 for South Indian, 3 for Other): " << std::endl;
    std::cin >> foodPreferenceInt;
    menuItem.foodPreference = static_cast<FoodPreference>(foodPreferenceInt);

    std::cout << "Enter sweet tooth preference (1 for Yes, 2 for No): " << std::endl;
    std::cin >> sweetToothPreferenceInt;
    menuItem.sweetToothPreference = static_cast<SweetToothPreference>(sweetToothPreferenceInt);

    auto menuItemData = SerializationUtility::serialize(menuItem);
    auto addMenuSerializedRequest = SerializationUtility::serializeOperation(operation, menuItemData);

    std::cout << "Sending addItem request to server\n";
    requestHandler->sendRequest(addMenuSerializedRequest);

    std::string menuItemAddedResponse = requestHandler->receiveResponse();

    std::cout << menuItemAddedResponse << std::endl;
}



void AdminInterface::showDeleteItemPrompt() {
    int menuItemId;
    Operation operation = Operation::DeleteMenuItem;

    std::cout << "Enter the Id of menu item to delete(watch it form View Menu): " << std::endl;
    std::cin>>menuItemId;
    std::string menuItemIdStr =  std::to_string(menuItemId);
    auto deleteMenuItemSerializedRequest = SerializationUtility::serializeOperation(operation,menuItemIdStr);

    requestHandler->sendRequest(deleteMenuItemSerializedRequest);
    
    std::string menuDeletedResponse = requestHandler->receiveResponse();
    
    std::cout<<menuDeletedResponse<<std::endl;
}

void AdminInterface::showMenuItemList() {
    Operation operation = Operation::ViewMenu;
    std::string viewMenuSerializedRequest = SerializationUtility::serializeOperation(operation, "");
    requestHandler->sendRequest(viewMenuSerializedRequest);

    std::string serializedMenuList = requestHandler->receiveResponse();

    std::vector<std::string>menuList = VectorSerializer::deserialize(serializedMenuList);

    for (const auto& item : menuList) {
         auto menuItem = SerializationUtility::deserialize<MenuItem>(item);

        std::string menuItemType = menuItem.menuItemType == MenuItemType::Breakfast ? "Breakfast" :
                                   menuItem.menuItemType == MenuItemType::Lunch ? "Lunch" :
                                   menuItem.menuItemType == MenuItemType::Dinner ? "Dinner" : "Unknown";

        std::string vegetarianPreferenceStr = menuItem.vegetarianPreference == VegetarianPreference::Vegetarian ? "Vegetarian" :
                                              menuItem.vegetarianPreference == VegetarianPreference::NonVegetarian ? "Non Vegetarian" :
                                              menuItem.vegetarianPreference == VegetarianPreference::Eggetarian ? "Eggetarian" : "Unknown";

        std::string spiceLevelOptionStr = menuItem.spiceLevelOption == SpiceLevelOption::High ? "High" :
                                          menuItem.spiceLevelOption == SpiceLevelOption::Medium ? "Medium" :
                                          menuItem.spiceLevelOption == SpiceLevelOption::Low ? "Low" : "Unknown";

        std::string foodPreferenceStr = menuItem.foodPreference == FoodPreference::NorthIndian ? "North Indian" :
                                        menuItem.foodPreference == FoodPreference::SouthIndian ? "South Indian" :
                                        menuItem.foodPreference == FoodPreference::Other ? "Other" : "Unknown";

        std::string sweetToothPreferenceStr = menuItem.sweetToothPreference == SweetToothPreference::Yes ? "Yes" : "No";

        std::cout << "Menu Item Details:" << std::endl
                  << "ID: " << menuItem.menuItemId << std::endl
                  << "Name: " << menuItem.menuItemName << std::endl
                  << "Type: " << menuItemType << std::endl
                  << "Availability: " << (menuItem.availability ? "Yes" : "No") << std::endl
                  << "Price: " << menuItem.price << std::endl
                  << "Vegetarian Preference: " << vegetarianPreferenceStr << std::endl
                  << "Spice Level Option: " << spiceLevelOptionStr << std::endl
                  << "Food Preference: " << foodPreferenceStr << std::endl
                  << "Sweet Tooth Preference: " << sweetToothPreferenceStr << std::endl;
        std::cout << std::endl;
    }
}


void AdminInterface::addUserPrompt() {
    User user;
    Operation operation = Operation::AddUser;

    std::cout << "Enter User name: " << std::endl;
    std::getline(std::cin >> std::ws, user.name);

    std::cout << "Enter User password: " << std::endl;
    std::getline(std::cin >> std::ws, user.password);

    int roleInt;
    std::cout << "Enter Role (1 for Admin, 2 for Chef, 3 for Employee): ";
    std::cin >> roleInt;
    user.role = static_cast<Role>(roleInt);

    auto userData = SerializationUtility::serialize(user);
    auto addUserSerializedRequest = SerializationUtility::serializeOperation(operation, userData);
    requestHandler->sendRequest(addUserSerializedRequest);

    std::string userAddedResponse = requestHandler->receiveResponse();
    std::cout<<userAddedResponse<<std::endl;
}