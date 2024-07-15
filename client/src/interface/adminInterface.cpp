#include "../../inc/interface/adminInterface.h"
#include "../../../common/utility/utility.h"
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
                     "3. Update menu item\n"
                     "4. View menu\n"
                     "5. Add user\n"
                     "6. Exit\n"<<std::endl;

        int adminChoice = Utility::getValidatedChoice(1, 6);

        if (adminChoice == 1) {
            showAddItemPrompt();
        } else if (adminChoice == 2) {
            showDeleteItemPrompt();
        } else if (adminChoice == 3) {
            showUpdateMenuItemPrompt();
        } else if (adminChoice == 4) {
            showMenuItemList();
        } else if (adminChoice == 5) {
            addUserPrompt();
        } else if (adminChoice == 6) {
            flag = false;
        } else {
            std::cout << "Invalid Choice" << std::endl;
        }
    }
}

void AdminInterface::showAddItemPrompt() {
    MenuItem menuItem;

    std::cout << "Enter Item name: " << std::endl;
    std::getline(std::cin >> std::ws, menuItem.menuItemName);

    std::cout << "Enter Item price:" << std::endl;
    std::cin >> menuItem.price;

    std::cout << "Enter Item availability: (0 for not available and 1 for available )" << std::endl;
    std::cin >> menuItem.availability;

    std::cout << "Enter meal type (1 for Breakfast, 2 for Lunch, 3 for Dinner): " << std::endl;
    int menuItemTypeInt;
    std::cin >> menuItemTypeInt;
    menuItem.menuItemType = static_cast<MenuItemType>(menuItemTypeInt);

    std::cout << "Enter vegetarian preference (1 for Vegetarian, 2 for Non Vegetarian, 3 for Eggetarian): " << std::endl;
    int vegetarianPreferenceInt;
    std::cin >> vegetarianPreferenceInt;
    menuItem.vegetarianPreference = static_cast<VegetarianPreference>(vegetarianPreferenceInt);

    std::cout << "Enter spice level option (1 for High, 2 for Medium, 3 for Low): " << std::endl;
    int spiceLevelOptionInt;
    std::cin >> spiceLevelOptionInt;
    menuItem.spiceLevelOption = static_cast<SpiceLevelOption>(spiceLevelOptionInt);

    std::cout << "Enter Cuisine Preference (1 for North Indian, 2 for South Indian, 3 for Other): " << std::endl;
    int cuisinePreferenceInt;
    std::cin >> cuisinePreferenceInt;
    menuItem.cuisinePreference = static_cast<CuisinePreference>(cuisinePreferenceInt);

    std::cout << "Enter sweet tooth preference (1 for Yes, 0 for No): " << std::endl;
    int sweetToothPreferenceInt;
    std::cin >> sweetToothPreferenceInt;
    menuItem.sweetToothPreference = static_cast<SweetToothPreference>(sweetToothPreferenceInt);

    auto menuItemData = SerializationUtility::serialize(menuItem);
    auto addMenuSerializedRequest = SerializationUtility::serializeOperation(Operation::AddMenuItem, menuItemData);

    requestHandler->sendRequest(addMenuSerializedRequest);

    std::string menuItemAddedResponse = requestHandler->receiveResponse();

    std::cout << menuItemAddedResponse << std::endl;
}

void AdminInterface::showDeleteItemPrompt() {
    int menuItemId;

    std::cout << "Enter the Id of menu item to delete(watch it form View Menu): " << std::endl;
    std::cin>>menuItemId;
    std::string menuItemIdStr =  std::to_string(menuItemId);
    auto deleteMenuItemSerializedRequest = SerializationUtility::serializeOperation(Operation::DeleteMenuItem,menuItemIdStr);

    requestHandler->sendRequest(deleteMenuItemSerializedRequest);
    
    std::string menuDeletedResponse = requestHandler->receiveResponse();
    
    std::cout<<menuDeletedResponse<<std::endl;
}


void AdminInterface::showUpdateMenuItemPrompt(){
    int menuItemId;

    std::cout << "Enter the Id of menu item to Update(watch it form View Menu): " << std::endl;
    std::cin>>menuItemId;
    std::string menuItemIdStr =  std::to_string(menuItemId);
    auto getMenuItemByIdSerializedRequest = SerializationUtility::serializeOperation(Operation::GetMenuItemById,menuItemIdStr);
    requestHandler->sendRequest(getMenuItemByIdSerializedRequest);
    
    std::string menuItemData = requestHandler->receiveResponse();
    MenuItem menuItem = SerializationUtility::deserialize<MenuItem>(menuItemData);
    displayMenuItemDetails(menuItem);

    MenuItem updatedMenuItem = updateMenuItemFromUserInput(menuItem);

    auto updatedMenuItemData = SerializationUtility::serialize(updatedMenuItem);
    auto updateMenuItemSerializedRequest = SerializationUtility::serializeOperation(Operation::UpdateMenuItem,updatedMenuItemData);
    requestHandler->sendRequest(updateMenuItemSerializedRequest);

    std::string menuItemUpdatedResponse = requestHandler->receiveResponse();
    std::cout<<menuItemUpdatedResponse<<std::endl;
}

MenuItem AdminInterface::updateMenuItemFromUserInput(MenuItem menuItem)
{
    bool flag = true;
    std::string userInput;
    while (flag)
    {
        std::cout<<"Enter the Index No. of the field you want to update or 0 to exit:-"<<std::endl;
        std::cin >> userInput;
        if(userInput == "0")
        {
            flag = false;
        }
        else if(userInput == "1")
        {
            std::cout << "Enter updated name:-" << std::endl;
            std::getline(std::cin >> std::ws, menuItem.menuItemName);
        }
        else if(userInput == "2")
        {
            int menuItemTypeInt;
            std::cout << "Enter updated meal type (1 for Breakfast, 2 for Lunch, 3 for Dinner): " << std::endl;
            std::cin >> menuItemTypeInt;
            menuItem.menuItemType = static_cast<MenuItemType>(menuItemTypeInt);
        }
        else if(userInput == "3")
        {
            std::cout << "Enter updated availability: (0 for not available and 1 for available )" << std::endl;
            std::cin >> menuItem.availability;
        }
        else if(userInput == "4")
        {
            std::cout << "Enter updated price:" << std::endl;
            std::cin >> menuItem.price;
        }
        else if(userInput == "5")
        {
            int vegetarianPreferenceInt;
            std::cout << "Enter updated vegetarian preference (1 for Vegetarian, 2 for Non Vegetarian, 3 for Eggetarian): " << std::endl;
            std::cin >> vegetarianPreferenceInt;
            menuItem.vegetarianPreference = static_cast<VegetarianPreference>(vegetarianPreferenceInt);
        }
        else if(userInput == "6")
        {
            int spiceLevelOptionInt;
            std::cout << "Enter updated spice level option (1 for High, 2 for Medium, 3 for Low): " << std::endl;
            std::cin >> spiceLevelOptionInt;
            menuItem.spiceLevelOption = static_cast<SpiceLevelOption>(spiceLevelOptionInt);
        }
        else if(userInput == "7")
        {
            int cuisinePreferenceInt;
            std::cout << "Enter updated Cuisine Preference (1 for North Indian, 2 for South Indian, 3 for Other): " << std::endl;
            std::cin >> cuisinePreferenceInt;
            menuItem.cuisinePreference = static_cast<CuisinePreference>(cuisinePreferenceInt);
        }
        else if(userInput == "8")
        {
            int sweetToothPreferenceInt;
            std::cout << "Enter updated sweet tooth preference (1 for Yes, 2 for No): " << std::endl;
            std::cin >> sweetToothPreferenceInt;
            menuItem.sweetToothPreference = static_cast<SweetToothPreference>(sweetToothPreferenceInt);
        }
        
    }
    return menuItem;
}

void AdminInterface::showMenuItemList() {
    std::string viewMenuSerializedRequest = SerializationUtility::serializeOperation(Operation::ViewMenu, "");
    requestHandler->sendRequest(viewMenuSerializedRequest);

    std::string serializedMenuList = requestHandler->receiveResponse();

    std::vector<std::string>menuList = SerializationUtility::deserializeStringToVector(serializedMenuList);
    std::cout << "***************Menu Item Details***************" << std::endl;
    for (const auto& item : menuList) {
        auto menuItem = SerializationUtility::deserialize<MenuItem>(item);
        displayMenuItemDetails(menuItem);
    }
}

void AdminInterface::addUserPrompt() {
    User user;

    std::cout << "Enter User name: " << std::endl;
    std::getline(std::cin >> std::ws, user.name);

    std::cout << "Enter User password: " << std::endl;
    std::getline(std::cin >> std::ws, user.password);

    int roleInt;
    std::cout << "Enter Role (1 for Admin, 2 for Chef, 3 for Employee): ";
    std::cin >> roleInt;
    user.role = static_cast<Role>(roleInt);

    auto userData = SerializationUtility::serialize(user);
    auto addUserSerializedRequest = SerializationUtility::serializeOperation(Operation::AddUser, userData);
    requestHandler->sendRequest(addUserSerializedRequest);

    std::string userAddedResponse = requestHandler->receiveResponse();
    std::cout<<userAddedResponse<<std::endl;
}

void AdminInterface::displayMenuItemDetails(const MenuItem& menuItem) {
    std::cout<<"**Menu Item ID: " << menuItem.menuItemId << std::endl
              << "   1. Name: " << menuItem.menuItemName << std::endl
              << "   2. Type: " << Utility::getMenuItemType(menuItem.menuItemType) << std::endl
              << "   3. Availability: " << (menuItem.availability ? "Yes" : "No") << std::endl
              << "   4. Price: " << menuItem.price << std::endl
              << "   5. Vegetarian Preference: " << Utility::getVegetarianPreference(menuItem.vegetarianPreference) << std::endl
              << "   6. Spice Level Option: " << Utility::getSpiceLevelOption(menuItem.spiceLevelOption) << std::endl
              << "   7. Cuisine Preference: " << Utility::getCuisinePreference(menuItem.cuisinePreference) << std::endl
              << "   8. Sweet Tooth Preference: " << Utility::getSweetToothPreference(menuItem.sweetToothPreference) << std::endl;
    std::cout<<std::endl;
}
