#include "../../inc/controller/chefController.h"

ChefController::ChefController(MenuItemService* menuItemService, NextDayMenuVotingService* nextDayMenuVotingService, FeedbackService* feedbackService, RecommendationEngine* recommendationEngine,TodayMenuService* todayMenuService, NotificationService* notificationService): 
        menuItemService(menuItemService), nextDayMenuVotingService(nextDayMenuVotingService), feedbackService(feedbackService), recommendationEngine(recommendationEngine), todayMenuService(todayMenuService), notificationService(notificationService) {}

std::string ChefController::handleRequest(Operation operation, std::string requestData) {
    std::cout<<"Handle request in Chef Controller\n"<<std::endl;
    std::string response = "";
    if (operation == Operation::ViewMenu) {
        std::vector<MenuItem> menuDetails = menuItemService->getAllMenuItems();
        std::vector<std::string> menuSerializedData;
        for (auto menu : menuDetails) {
            menuSerializedData.push_back(SerializationUtility::serialize(menu));
        }
        response = VectorSerializer::serialize(menuSerializedData);
        std::cout<<"operationDOne : view menu data send"<<std::endl;
    }
    else if(operation == Operation::RollOutMenuForNextDay){
        std::cout<<"Inside RollOutMenuForNextDay"<<std::endl;
        std::vector<std::string> menuItemIdToRollOutMenu = VectorSerializer::deserialize(requestData, '$');
        std::vector<int> menuItemIdsForNextDayMenu;
        for(auto menuItemForMenuType : menuItemIdToRollOutMenu){
            std::vector<std::string> menuItemIds = VectorSerializer::deserialize(menuItemForMenuType, ',');
            for(auto menuItemId : menuItemIds){
                menuItemIdsForNextDayMenu.push_back(std::stoi(menuItemId));
            }
        }
        bool operationDone = rollOutFinalMenuByChefForNextDay(menuItemIdsForNextDayMenu);
        pushNotification(operation);
    }
    else if(operation == Operation::GetRecommandationFromEngine){
       std::vector<NextDayMenuRollOut> recommendedMenuItem = getTopMenuRecommendationFromEngine(static_cast<MenuItemType>(std::stoi(requestData)));
       std::vector<std::string> recommendedMenuItemSerializedData;
        for (auto menu : recommendedMenuItem) {
            recommendedMenuItemSerializedData.push_back(SerializationUtility::serialize(menu));
        }
        response = VectorSerializer::serialize(recommendedMenuItemSerializedData);
        std::cout<<"operationDOne : Recommended Menu from Engine Send"<<std::endl;

    }else if(operation == Operation::PublishMenuForToday){
        response = std::to_string(publishMostVotedMenuItems());
        pushNotification(operation);
    }else {
        response = "Invalid operation";
    }
    return response;
    
}


std::vector<NextDayMenuRollOut> ChefController::getTopMenuRecommendationFromEngine(MenuItemType menuItemType){
    std::cout<<"Inside getTopMenuRecommendationFromEngine"<<std::endl;
    std::unordered_map<int, std::vector<Feedback>> feedbackMap = feedbackService->getAllFeedbacks();
    std::vector<MenuItem> menuItems = menuItemService->getAllMenuItems();
    std::vector<NextDayMenuVoting>  nextDayMenuRecommendationForMenuType = recommendationEngine->recommendTopFoodItems(menuItemType, feedbackMap, menuItems);
    nextDayMenuRecommendation.insert(nextDayMenuRecommendation.end(),
                                     nextDayMenuRecommendationForMenuType.begin(),
                                     nextDayMenuRecommendationForMenuType.end());
    return getNextDayMenuItemsToRollOut(nextDayMenuRecommendationForMenuType);
}


std::vector<NextDayMenuRollOut> ChefController::getNextDayMenuItemsToRollOut(std::vector<NextDayMenuVoting> nextDayMenuToRollOut) {
    std::vector<NextDayMenuRollOut> nextDayMenuRollOutItems;

    for (const auto& nextDayMenuItemId : nextDayMenuToRollOut) {
        // Retrieve the menu item details using menuService
        MenuItem menuItem = menuItemService->getMenuItemById(nextDayMenuItemId.menuItemId);

        // Create NextDayMenuRollOut object
        NextDayMenuRollOut rollOutItem(
            menuItem.menuItemId,
            menuItem.menuItemName,
            menuItem.menuItemType,
            menuItem.price,
            nextDayMenuItemId.voteCount,        // Assuming this should be set as selectionCount
            nextDayMenuItemId.rating,
            nextDayMenuItemId.sentimentScore
        );

        // Add to the result vector
        nextDayMenuRollOutItems.push_back(rollOutItem);
    }

    return nextDayMenuRollOutItems;
}


bool ChefController::rollOutFinalMenuByChefForNextDay(std::vector<int> menuItemId){
    std::cout<<"rollOutFinalMenuByChefForNextDay : entry"<<std::endl;
    std::vector<NextDayMenuVoting> finalChefMenuForNextDay;

    for (auto menuId : menuItemId) {
        auto it = std::find_if(nextDayMenuRecommendation.begin(), nextDayMenuRecommendation.end(),
                               [&menuId](const NextDayMenuVoting& voting) {
                                   return voting.menuItemId == menuId;
                               });

        if (it != nextDayMenuRecommendation.end()) {
            finalChefMenuForNextDay.push_back(*it);
        }else{
            std::cout<<"Item Not founded in Recommendation Engine suggestion"<<std::endl;
        }
    }

    for (auto menuId : finalChefMenuForNextDay) {
        std::cout<<"MenuItemId got"<<menuId.menuItemId<<"\t";
    }

    std::cout<<"Adding data of recommended Menu into table by chef"<<std::endl;
    nextDayMenuVotingService->deleteMenuRolledOut();
    bool operationDone = nextDayMenuVotingService->addNextDayMenuRollout(finalChefMenuForNextDay);
    nextDayMenuRecommendation.clear();
    return operationDone;
}

bool ChefController::publishMostVotedMenuItems(){
    std::vector<int> mostVotedMenuItemIds = nextDayMenuVotingService->getMostVotedMenuItemIds();
    bool menuItemAdded = todayMenuService->addTodayMenu(mostVotedMenuItemIds);
    return menuItemAdded;
}

bool ChefController::pushNotification(Operation operation) {
    Notification notification;
    if(Operation::PublishMenuForToday == operation) {
        notification.notificationTitle = "Today's Menu Published";
        notification.message = "Today's Menu has been published";
    }else {
        notification.notificationTitle = "Menu RollOut For Next Day";
        notification.message = "Chef had RollOut Menu Item For Next Day check it out in the UserMenu";
    }

    return notificationService->addNotification(notification);
}