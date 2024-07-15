#include "../../inc/interface/chefInterface.h"
#include "../../../common/utility/utility.h"
#include <iostream>
#include <limits> 
#include <vector>
#include <stdexcept>
#include <algorithm>

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
                         "3. View Voting list of Next Day Menu\n"
                         "4. Publish Menu For Today\n"
                         "5. Discard Menu Item List\n"
                         "6. Exit\n" << std::endl;

            int chefChoice = Utility::getValidatedChoice(1, 6);

            if (chefChoice == 1) {
                showMenuItemList();
            } else if (chefChoice == 2) {
                showRecommendedMenuAndRolloutForTomorrow();
            } else if (chefChoice == 3) {
                showNextDayMenuVoting();
            } else if (chefChoice == 4) {
                publishMenuForToday();
            } else if (chefChoice == 5) {
                showDiscardMenuList();
            } else if (chefChoice == 6) {
                flag = false;
            } else {
                std::cout << "Invalid Choice" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

void ChefInterface::showMenuItemList() {
    try {
        std::string viewMenuSerializedRequest = SerializationUtility::serializeOperation(Operation::ViewMenu, "");
        requestHandler->sendRequest(viewMenuSerializedRequest);

        std::string serializedMenuList = requestHandler->receiveResponse();

        std::vector<std::string>menuList = SerializationUtility::deserializeStringToVector(serializedMenuList);
        std::cout << "***************Menu Item Details***************" << std::endl;
        for (const auto& item : menuList) {
            auto menuItem = SerializationUtility::deserialize<MenuItem>(item);

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
    } catch (const std::exception& e) {
        std::cerr << "Error in showing menu item list: " << e.what() << std::endl;
        throw;
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
                        "5. Exit\n" << std::endl;

            int userChoice = Utility::getValidatedChoice(1, 5);

            if(userChoice > 0 && userChoice < 4){
                MenuItemType menuItemType = static_cast<MenuItemType>(userChoice);
                std::vector<std::pair<MenuItemType, int>> recommendedMenuItemForMealType = showRecommendedMenu(menuItemType);
                recommendedMenuItem.insert(recommendedMenuItem.end(), recommendedMenuItemForMealType.begin(), recommendedMenuItemForMealType.end());
            } else if(userChoice == 4){
                if(recommendedMenuItem.empty()){
                    std::cout<<"Please get Recommendation Menu First\n";
                    continue;
                }
                rollOutMenuForTomorrow(recommendedMenuItem);
                flag = false;
            } else if(userChoice == 5){
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
        std::string mealtype = std::to_string(menuItemType);
        std::string viewMenuSerializedRequest = SerializationUtility::serializeOperation(Operation::GetRecommandationFromEngine, mealtype);
        requestHandler->sendRequest(viewMenuSerializedRequest);

        std::string serializedMenuList = requestHandler->receiveResponse();

        std::vector<std::string>MenuList = SerializationUtility::deserializeStringToVector(serializedMenuList);
        std::cout<< "********************Recommend Menu Items For "<<Utility::getMenuItemType(menuItemType)<<" ********************" << std::endl<<std::endl;
        
        for (const auto& item : MenuList) {
            auto menuItem = SerializationUtility::deserialize<NextDayMenuRollOut>(item);
            recommendedMenuItem.push_back(std::make_pair(menuItem.menuItemType, menuItem.menuItemId));
            std::cout << "Menu Item ID: " << menuItem.menuItemId << "\t"
              << "Menu Item Name: " << menuItem.menuItemName << "\t"
              << "Menu Item Type: " << Utility::getMenuItemType(menuItem.menuItemType) << "\t"
              << "Price: " << menuItem.price << "\t"
              << "Average Rating: " << menuItem.averageRating << "\t"
              << "Sentiments : " << menuItem.sentiments << std::endl;
        }
        std::cout<<std::endl;
        return recommendedMenuItem;
    } catch (const std::exception& e) {
        std::cerr << "Error in showing recommended menu: " << e.what() << std::endl;
        throw;
    }
}

void ChefInterface::rollOutMenuForTomorrow(std::vector<std::pair<MenuItemType, int>> recommendedMenuItem){
    try {
        std::cout<<"Roll out Menu For Tomorrow (choose MenuItem Id from Recommended Items)\n";
        
        std::vector<std::string> chefRollOutMenuForTomorrow;
        for (int i = 1; i < 4; ++i) {
            std::string menuItemIdsforMealType = getValidMenuItemIdsForMealType(recommendedMenuItem, static_cast<MenuItemType>(i));
            chefRollOutMenuForTomorrow.push_back(menuItemIdsforMealType);
        }

        std::string serializeRequestData = SerializationUtility::serializeStringVector(chefRollOutMenuForTomorrow);

        std::string serializedRequestWithOperation = SerializationUtility::serializeOperation(Operation::RollOutMenuForNextDay, serializeRequestData);
        requestHandler->sendRequest(serializedRequestWithOperation);
        std::string response = requestHandler->receiveResponse();
        std::cout<<response<<std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in rolling out menu for tomorrow: " << e.what() << std::endl;
    }
}

std::string ChefInterface::getValidMenuItemIdsForMealType(const std::vector<std::pair<MenuItemType, int>>& recommendedMenuItem, MenuItemType menuItemType) {
    try {
        std::cout << "Enter MenuItemIds for "<<Utility::getMenuItemType(menuItemType)<<" : ";
        while (true) {
            std::string menuItemIdsForMealType;
            std::cin >> menuItemIdsForMealType;
        
            std::string notRecommendedMenuItemIds = validateMenuItemsAgainstRecommendedItems(recommendedMenuItem, menuItemIdsForMealType, menuItemType);
            
            if (notRecommendedMenuItemIds.empty()) {
                return menuItemIdsForMealType;
            } else {
                std::cout << "Invalid Menu Item IDs: " << notRecommendedMenuItemIds << std::endl;
                std::cout<<"Please Enter Valid Menu Item Ids\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in getting valid menu item IDs for meal type: " << e.what() << std::endl;
        throw;
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
        throw;
    }
}


void ChefInterface::showNextDayMenuVoting(){
    try {
        std::string viewNextDayMenuVotingSerializedRequest = SerializationUtility::serializeOperation(Operation::GetNextDayMenuVoting, "");
        requestHandler->sendRequest(viewNextDayMenuVotingSerializedRequest);

        std::string serializedMenuList = requestHandler->receiveResponse();
        if(serializedMenuList == "0"){
            std::cout<<"No Voting as Menu is not yet rolled out\n";
            return;
        }

        std::vector<std::string>MenuList = SerializationUtility::deserializeStringToVector(serializedMenuList);
        std::cout<< "********************Next Day Menu Voting********************" << std::endl;
        for (const auto& item : MenuList) {
            auto menuItem = SerializationUtility::deserialize<NextDayMenuRollOut>(item);
            std::cout<< "Menu Item Name: " << menuItem.menuItemName << "\t"
              << "Votes : " << menuItem.selectionCount << "\n"<<std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in showing next day menu voting: " << e.what() << std::endl;
    }
}




void ChefInterface::publishMenuForToday(){
    try {
        std::string publishMenuSerializedRequest = SerializationUtility::serializeOperation(Operation::PublishMenuForToday, "");
        requestHandler->sendRequest(publishMenuSerializedRequest);
        std::string response = requestHandler->receiveResponse();
        std::vector<std::string> publishedMenuList = SerializationUtility::deserializeStringToVector(response);
        std::cout<< "********************Published Menu of Most Voted Menu Items For Today********************" << std::endl;
        for(const auto& item : publishedMenuList){
            auto menuItem = SerializationUtility::deserialize<MenuItem>(item);
            std::cout << "Menu Item ID: " << menuItem.menuItemId << "\n"
              << "Menu Item Name: " << menuItem.menuItemName << "\n"
              << "Menu Item Type: " << Utility::getMenuItemType(menuItem.menuItemType) << "\n"
              << "Price: " << menuItem.price << "\n\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in publishing menu for today: " << e.what() << std::endl;
    }
}

void ChefInterface::showDiscardMenuList(){
    try {
        std::string viewDiscardMenuSerializedRequest = SerializationUtility::serializeOperation(Operation::GetDiscardMenuList, "");
        requestHandler->sendRequest(viewDiscardMenuSerializedRequest);

        std::string serializedMenuList = requestHandler->receiveResponse();

        std::vector<std::string>MenuList = SerializationUtility::deserializeStringToVector(serializedMenuList);
        std::cout<< "Menu Item Details:" << std::endl;
        std::vector<int> discardMenuItemIdList = {};
        std::cout<< "********************Discard Menu List********************" << std::endl;
        for (const auto& item : MenuList) {
            auto menuItem = SerializationUtility::deserialize<NextDayMenuRollOut>(item);
            discardMenuItemIdList.push_back(menuItem.menuItemId);
            std::cout << "Menu Item ID: " << menuItem.menuItemId << "\t"
              << "Menu Item Name: " << menuItem.menuItemName << "\t"
              << "Menu Item Type: " << Utility::getMenuItemType(menuItem.menuItemType)<< "\t"
              << "Price: " << menuItem.price << "\t"
              << "Average Rating: " << menuItem.averageRating << "\t"
              << "Sentiments : " << menuItem.sentiments << std::endl<<std::endl;
        }

        showDiscardMenuItemActionPrompt(discardMenuItemIdList);
    } catch (const std::exception& e) {
        std::cerr << "Error in showing recommended menu: " << e.what() << std::endl;
        throw;
    }
}


void ChefInterface::showDiscardMenuItemActionPrompt(const std::vector<int>& discardMenuItemIdList){
    bool flag = true;
    while (flag) {
        try {
            std::cout << "Select the operation which you like to perform\n"
                         "1. Select Menu Item ID to delete from the menu:\n"
                         "2. Select the Menu Item ID to receive detailed feedback:\n"
                         "3. Exit\n" << std::endl;

            int discardMenuChoice = Utility::getValidatedChoice(1, 3);
            
            if (discardMenuChoice == 1) {
                removeMenuItemFromList(discardMenuItemIdList);
            } else if (discardMenuChoice == 2) {
                getMenuItemIdForDetailedFeedback(discardMenuItemIdList);
            } else if (discardMenuChoice == 3) {
                flag = false;
            } else {
                std::cout << "Invalid Choice" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

void ChefInterface::removeMenuItemFromList(const std::vector<int>& discardMenuItemIdList){
    try {
        std::cout << "**********Remove Menu Item from List**********\n";
        std::cout << "Provide the Menu Item ID to delete: ";
        int menuItemId;
        std::cin >> menuItemId;

        if (std::find(discardMenuItemIdList.begin(), discardMenuItemIdList.end(), menuItemId) == discardMenuItemIdList.end()) {
            std::cout << "Invalid Menu Item ID" << std::endl;
            return;
        }

        std::string removeMenuItemSerializedRequest = SerializationUtility::serializeOperation(Operation::RemoveMenuItemFromList, std::to_string(menuItemId));
        requestHandler->sendRequest(removeMenuItemSerializedRequest);

        std::cout<<requestHandler->receiveResponse()<<std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in removing menu item from list: " << e.what() << std::endl;
    }
}

void ChefInterface::getMenuItemIdForDetailedFeedback(const std::vector<int>& discardMenuItemIdList){
    try {
        std::cout<<"Get MenuItem Id For Detailed Feedback\n";
        std::cout << "Enter MenuItemId to Get Detailed Feedback: ";
        int menuItemId;
        std::cin >> menuItemId;

        if (std::find(discardMenuItemIdList.begin(), discardMenuItemIdList.end(), menuItemId) == discardMenuItemIdList.end()) {
            std::cout << "Invalid Menu Item ID" << std::endl;
            return;
        }

        std::string getDetailedFeedbackSerializedRequest = SerializationUtility::serializeOperation(Operation::GetMenuItemIdForDetailFeedbackFromChef, std::to_string(menuItemId));
        requestHandler->sendRequest(getDetailedFeedbackSerializedRequest);

        std::cout<<requestHandler->receiveResponse()<<std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error in getting menu item ID for detailed feedback: " << e.what() << std::endl;
    }

}