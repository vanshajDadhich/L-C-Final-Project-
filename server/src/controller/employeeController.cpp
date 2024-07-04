#include "../../inc/controller/employeeController.h"

EmployeeController::EmployeeController(FeedbackService* feedbackService, NextDayMenuVotingService* nextDayMenuVotingService, MenuItemService* menuItemService, TodayMenuService* todayMenuService, NotificationService* notificationService, DiscardMenuItemDetailedFeedbackService* discardMenuItemDetailedFeedbackService, UserProfileService* userProfileService, RecommendationEngine* recommendationEngine) 
        : feedbackService(feedbackService), nextDayMenuVotingService(nextDayMenuVotingService), menuItemService(menuItemService), todayMenuService(todayMenuService), notificationService(notificationService), discardMenuItemDetailedFeedbackService(discardMenuItemDetailedFeedbackService), userProfileService(userProfileService), recommendationEngine(recommendationEngine){}


std::string EmployeeController::handleRequest(Operation operation,std::string request) {
    std::cout<<"Handle request in Chef Controller\n";
    std::string response;
    if (operation == Operation::ViewNotification) {
        std::vector<Notification> notificationDetails = notificationService->getAllNotifications();
        std::vector<std::string> notificationSerializedData;
        for (auto notification : notificationDetails) {
            notificationSerializedData.push_back(SerializationUtility::serialize(notification));
        }
        response = VectorSerializer::serialize(notificationSerializedData);
    }
    else if(operation == Operation::ProvideFeedback){
        Feedback feedback = SerializationUtility::deserialize<Feedback>(request);
        bool operationDone = feedbackService->addFeedback(feedback);
        std::cout<<"FeedBack Added : "<<operationDone<<std::endl;
    }
    else if(operation == Operation::GetTodaysMenu){
        std::vector<MenuItem> todaysMenu = todayMenuService->getAllTodayMenuItem();
        std::vector<std::string> serializedMenuItem;
        for (auto menuItem : todaysMenu) {
            serializedMenuItem.push_back(SerializationUtility::serialize(menuItem));
        }
        response = VectorSerializer::serialize(serializedMenuItem);
    }
    else if(operation == Operation::VoteItemFromTomorrowMenu){
        int menuItemId = std::stoi(request);
        bool operationDone = nextDayMenuVotingService->increaseVoteCountForMenuItemId(menuItemId);
        std::cout<<"Increased Count for menuItemID provided"<<std::endl;
    }
    else if(operation == Operation::GetChefRollOutMenuForTomorrow)
    {  
        int userId = std::stoi(request);
        std::vector<NextDayMenuRollOut> preferenceBasedNextDayMenuRollOut = {};
        std::vector<NextDayMenuRollOut> chefRolloutMenuForNextDay = getNextDayMenuItemsToRollOut();
        for(int i=0; i<3; i++){
            auto chefRollOutMenuForMealType = filterMenuItemsByType(static_cast<MenuItemType>(i+1), chefRolloutMenuForNextDay);
            chefRollOutMenuForMealType = recommendationEngine->sortRecommendedMenuItemsBasedOnProfile(userProfileService->getUserProfileByID(userId), chefRollOutMenuForMealType, menuItemService->getAllMenuItems());
            preferenceBasedNextDayMenuRollOut.insert(preferenceBasedNextDayMenuRollOut.end(), chefRollOutMenuForMealType.begin(), chefRollOutMenuForMealType.end());
        }
        std::vector<std::string> recommendedMenuItemSerializedData;
        for (auto menu : preferenceBasedNextDayMenuRollOut) {
            recommendedMenuItemSerializedData.push_back(SerializationUtility::serialize(menu));
        }
        response = VectorSerializer::serialize(recommendedMenuItemSerializedData);

    }else if(operation == Operation::provideDiscardMenuItemDetailedFeedback){
        DiscardMenuItemDetailedFeedback feedback = SerializationUtility::deserialize<DiscardMenuItemDetailedFeedback>(request);
        std::cout<<"Feedback Received : "<<feedback.menuItemId<<" userId : "<<feedback.userId<<" whatYouLiked : "<<feedback.whatYouLiked<<" howWouldItTaste : "<<feedback.howWouldItTaste<<" shareRecipe : "<<feedback.shareRecipe<<std::endl;
        int operationDone = discardMenuItemDetailedFeedbackService->addFeedback(feedback);
        response = "Discard Menu Item Detail Feedback Added\n";
        std::cout<<"Feedback Added : "<<operationDone<<std::endl;
    }
    else {
        response = "Invalid operation";
    }
    return response;
}

std::vector<NextDayMenuRollOut> EmployeeController::getNextDayMenuItemsToRollOut() {
    std::vector<NextDayMenuVoting> nextDayMenuVotingList = nextDayMenuVotingService->getAllNextDayMenuRollOutItem();
    std::vector<NextDayMenuRollOut> nextDayMenuRollOutItems;

    for (const auto& nextDayMenuItemId : nextDayMenuVotingList) {
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
            nextDayMenuItemId.sentiments
        );

        // Add to the result vector
        nextDayMenuRollOutItems.push_back(rollOutItem);
    }

    return nextDayMenuRollOutItems;
}

std::vector<NextDayMenuRollOut> EmployeeController::filterMenuItemsByType(
    MenuItemType menuItemType,
    const std::vector<NextDayMenuRollOut>& chefRolloutMenuForNextDay) {

    std::vector<NextDayMenuRollOut> filteredMenuItems;
    for (const auto& menuItem : chefRolloutMenuForNextDay) {
        if (menuItem.menuItemType == menuItemType) {
            filteredMenuItems.push_back(menuItem);
        }
    }

    return filteredMenuItems;
}
