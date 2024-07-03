#include "../inc/chefInterface.h"
#include <iostream>
#include <limits> 
#include <vector>
#include <stdexcept> // For std::runtime_error

ChefInterface::ChefInterface(RequestHandler* requestHandler)
    : requestHandler(requestHandler) {}

void ChefInterface::showMenu(){
    std::cout << "Welcome Chef\n\n";
    bool flag = true;
    while (flag) {
        try {
            std::cout << "Select the operation which you like to perform\n"
                         "1. View Menu\n"
                         "2. Get Recommendation Menu and Roll out Menu For tomorrow\n"
                         "3. Publish Menu For Today\n"
                         "4. Discard Menu Item List\n"
                         "5. Exit\n"
                         "Enter your choice: " << std::endl;

            int chefChoice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (!(std::cin >> chefChoice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number between 1 and 4: " << std::endl;
            }

            switch (chefChoice) {
                case 1:
                    showMenuItemList();
                    break;
                case 2:
                    showRecommendedMenuAndRolloutForTomorrow();
                    break;
                case 3:
                    publishMenuForToday();
                    break;
                case 4:
                    showDiscardMenuList();
                    break;
                case 5:
                    flag = false;
                    break;
                default:
                    std::cout << "Invalid Choice" << std::endl;
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}


void ChefInterface::showDiscardMenuList(){
    try {
        Operation operation = Operation::GetDiscardMenuList;
        std::string viewDiscardMenuSerializedRequest = SerializationUtility::serializeOperation(operation, "");
        requestHandler->sendRequest(viewDiscardMenuSerializedRequest);

        std::string serializedMenuList = requestHandler->receiveResponse();

        std::cout<<"serializedMenuList"<<serializedMenuList<<std::endl;

        std::vector<std::string>MenuList = VectorSerializer::deserialize(serializedMenuList);
        std::cout<< "Menu Item Details:" << std::endl;
        std::vector<int> discardMenuItemIdList = {};
        
        for (const auto& item : MenuList) {
            auto menuItem = SerializationUtility::deserialize<NextDayMenuRollOut>(item);
            discardMenuItemIdList.push_back(menuItem.menuItemId);
            std::cout << "Menu Item ID: " << menuItem.menuItemId << "\t"
              << "Menu Item Name: " << menuItem.menuItemName << "\t"
              << "Menu Item Type: " << static_cast<int>(menuItem.menuItemType) << "\t"
              << "Price: " << menuItem.price << "\t"
              << "Average Rating: " << menuItem.averageRating << "\t"
              << "Sentiments : " << menuItem.sentiments << std::endl;
        }

        showDiscardMenuItemActionPrompt(discardMenuItemIdList);
    } catch (const std::exception& e) {
        std::cerr << "Error in showing recommended menu: " << e.what() << std::endl;
        throw; // Re-throw the exception to propagate it
    }
}


void ChefInterface::showDiscardMenuItemActionPrompt(const std::vector<int>& discardMenuItemIdList){
    bool flag = true;
    while (flag) {
        try {
            std::cout << "Select the operation which you like to perform\n"
                         "1. Select MenuItem Id to Remove From Menu List\n"
                         "2. Select MenuItem Id Get Detailed Feedback\n"
                         "3. Exit\n"
                         "Enter your choice: " << std::endl;

            int discardMenuChoice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (!(std::cin >> discardMenuChoice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number between 1 and 3: " << std::endl;
            }

            switch (discardMenuChoice) {
                case 1:
                    removeMenuItemFromList(discardMenuItemIdList);
                    break;
                case 2:
                    getMenuItemIdForDetailedFeedback(discardMenuItemIdList);
                    break;
                case 3:
                    flag = false;
                    break;
                default:
                    std::cout << "Invalid Choice" << std::endl;
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

void ChefInterface::getMenuItemIdForDetailedFeedback(const std::vector<int>& discardMenuItemIdList){
    try {
        std::cout<<"Get MenuItem Id For Detailed Feedback\n";
        std::cout << "Enter MenuItemId to Get Detailed Feedback: ";
        int menuItemId;
        std::cin >> menuItemId;

        bool found = false;
        for (int id : discardMenuItemIdList) {
            if (id == menuItemId) {
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Invalid Menu Item ID" << std::endl;
            return;
        }

        Operation operation = Operation::GetDiscardMenuItemDetailedFeedback;
        std::string getDetailedFeedbackSerializedRequest = SerializationUtility::serializeOperation(operation, std::to_string(menuItemId));
        requestHandler->sendRequest(getDetailedFeedbackSerializedRequest);

        std::string response = requestHandler->receiveResponse();
        std::cout<<response<<std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error in getting menu item ID for detailed feedback: " << e.what() << std::endl;
    }

}

void ChefInterface::removeMenuItemFromList(const std::vector<int>& discardMenuItemIdList){
    try {
        std::cout<<"Remove Menu Item From List\n";
        std::cout << "Enter MenuItemId to Remove From Menu List: ";
        int menuItemId;
        std::cin >> menuItemId;

        bool found = false;
        for (int id : discardMenuItemIdList) {
            if (id == menuItemId) {
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Invalid Menu Item ID" << std::endl;
            return;
        }

        Operation operation = Operation::RemoveMenuItemFromList;
        std::string removeMenuItemSerializedRequest = SerializationUtility::serializeOperation(operation, std::to_string(menuItemId));
        requestHandler->sendRequest(removeMenuItemSerializedRequest);
        std::string response = requestHandler->receiveResponse();
        std::cout<<response<<std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in removing menu item from list: " << e.what() << std::endl;
    }
}


void ChefInterface::rollOutMenuForTomorrow(std::vector<std::pair<MenuItemType, int>> recommendedMenuItem){
    try {
        Operation operation = Operation::RollOutMenuForNextDay;
        std::cout<<"Roll out Menu For Tomorrow (choose MenuItem Id from Recommended Items)\n"
                 <<"Select MenuItemID for BreakFast seprated by comma \n";
        
        std::vector<std::string> chefRollOutMenuForTomorrow;
        for (int i = 1; i < 2; ++i) {
            std::string menuItemIdsforMealType = getValidMenuItemIdsForMealType(recommendedMenuItem, static_cast<MenuItemType>(i));
            chefRollOutMenuForTomorrow.push_back(menuItemIdsforMealType);
        }

        std::string serializeRequestData = VectorSerializer::serialize(chefRollOutMenuForTomorrow);

        std::string serializedRequestWithOperation = SerializationUtility::serializeOperation(operation, serializeRequestData);
        std::cout<<"Roll Out Menu Serialized Data"<<serializedRequestWithOperation<<std::endl;
        requestHandler->sendRequest(serializedRequestWithOperation);
    } catch (const std::exception& e) {
        std::cerr << "Error in rolling out menu for tomorrow: " << e.what() << std::endl;
    }
}

std::string ChefInterface::getValidMenuItemIdsForMealType(const std::vector<std::pair<MenuItemType, int>>& recommendedMenuItem, MenuItemType menuItemType) {
    try {
        std::string menuItemIdsforBreakfast;
        std::string menuItemTypeStr = menuItemType == MenuItemType::Breakfast ? "Breakfast" : menuItemType == MenuItemType::Lunch ? "Lunch" : "Dinner";
        std::cout << "Enter MenuItemIds for "<<menuItemTypeStr<<" : ";
        std::cin >> menuItemIdsforBreakfast;
        
        while (true) {
            std::string notRecommendedMenuItemIds = validateMenuItemsAgainstRecommendedItems(recommendedMenuItem, menuItemIdsforBreakfast, menuItemType);
            
            if (notRecommendedMenuItemIds.empty()) {
                return menuItemIdsforBreakfast;
            } else {
                std::cout << "Invalid Menu Item IDs for "<<menuItemTypeStr<<" : " << notRecommendedMenuItemIds << "\n";
                std::cout << "Enter MenuItemIds for "<<menuItemTypeStr<<" again: ";
                std::cin >> menuItemIdsforBreakfast;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in getting valid menu item IDs for meal type: " << e.what() << std::endl;
        throw; // Re-throw the exception to propagate it
    }
}

void ChefInterface::publishMenuForToday(){
    try {
        std::cout<<"publishMenuForToday";
        Operation operation = Operation::PublishMenuForToday;
        std::string publishMenuSerializedRequest = SerializationUtility::serializeOperation(operation, "");
        requestHandler->sendRequest(publishMenuSerializedRequest);
    } catch (const std::exception& e) {
        std::cerr << "Error in publishing menu for today: " << e.what() << std::endl;
    }
}


void ChefInterface::showRecommendedMenuAndRolloutForTomorrow(){
    try {
        bool flag = true;
        std::vector<std::pair<MenuItemType, int>> recommendedMenuItem = {};
        while (flag) {
            std::cout << "Select the MealType you would like to get Recommendation for and Roll Out Menu For Tomorrow\n"
                        "1. BreakFast\n"
                        "2. Lunch\n"
                        "3. Dinner\n"
                        "4. Roll out Menu For Tomorrow\n"
                        "5. Exit\n"
                        "Enter your choice: " << std::endl;

            int userInput;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (!(std::cin >> userInput)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number between 1 and 5: " << std::endl;
            }

            if(userInput > 0 && userInput < 4){
                MenuItemType menuItemType = static_cast<MenuItemType>(userInput);
                std::vector<std::pair<MenuItemType, int>> recommendedMenuItemForMealType = showRecommendedMenu(menuItemType);
                recommendedMenuItem.insert(recommendedMenuItem.end(), recommendedMenuItemForMealType.begin(), recommendedMenuItemForMealType.end());
            } else if(userInput == 4){
                if(recommendedMenuItem.empty()){
                    std::cout<<"Please get Recommendation Menu First\n";
                    continue;
                }
                rollOutMenuForTomorrow(recommendedMenuItem);
            } else if(userInput == 5){
                flag = false;
            } else {
                std::cout << "Invalid Choice" << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in selecting meal type for recommendation menu: " << e.what() << std::endl;
    }
}

std::vector<std::pair<MenuItemType, int>> ChefInterface::showRecommendedMenu(MenuItemType menuItemType){
    try {
        std::vector<std::pair<MenuItemType, int>> recommendedMenuItem;
        Operation operation = Operation::GetRecommandationFromEngine;
        std::string mealtype = std::to_string(menuItemType);
        std::string viewMenuSerializedRequest = SerializationUtility::serializeOperation(operation, mealtype);
        requestHandler->sendRequest(viewMenuSerializedRequest);

        std::string serializedMenuList = requestHandler->receiveResponse();

        std::vector<std::string>MenuList = VectorSerializer::deserialize(serializedMenuList);
        std::cout<< "Menu Item Details:" << std::endl;
        
        for (const auto& item : MenuList) {
            auto menuItem = SerializationUtility::deserialize<NextDayMenuRollOut>(item);
            recommendedMenuItem.push_back(std::make_pair(menuItem.menuItemType, menuItem.menuItemId));
            std::cout << "Menu Item ID: " << menuItem.menuItemId << "\t"
              << "Menu Item Name: " << menuItem.menuItemName << "\t"
              << "Menu Item Type: " << static_cast<int>(menuItem.menuItemType) << "\t"
              << "Price: " << menuItem.price << "\t"
              << "Average Rating: " << menuItem.averageRating << "\t"
              << "Sentiments : " << menuItem.sentiments << std::endl;
        }

        return recommendedMenuItem;
    } catch (const std::exception& e) {
        std::cerr << "Error in showing recommended menu: " << e.what() << std::endl;
        throw; // Re-throw the exception to propagate it
    }
}

void ChefInterface::showMenuItemList() {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error in showing menu item list: " << e.what() << std::endl;
        throw; // Re-throw the exception to propagate it
    }
}

std::string ChefInterface::validateMenuItemsAgainstRecommendedItems(const std::vector<std::pair<MenuItemType, int>>& recommendedMenuItem,
                              const std::string& menuItemString,
                              MenuItemType menuItemType) {
    try {
        std::stringstream ss(menuItemString);
        std::string menuItemIdStr;
        std::vector<int> menuItemIds;
        std::string invalidItems;

        while (std::getline(ss, menuItemIdStr, ',')) {
            int menuItemId = std::stoi(menuItemIdStr);
            menuItemIds.push_back(menuItemId);
        }

        // Check each menuItemId against recommendedMenuItem
        for (int menuItemId : menuItemIds) {
            bool found = false;
            for (const auto& item : recommendedMenuItem) {
                if (item.first == menuItemType && item.second == menuItemId) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                if (!invalidItems.empty()) {
                    invalidItems += ",";
                }
                invalidItems += std::to_string(menuItemId);
            }
        }

        return invalidItems;
    } catch (const std::exception& e) {
        std::cerr << "Error in validating menu items against recommended items: " << e.what() << std::endl;
        throw; // Re-throw the exception to propagate it
    }
}
