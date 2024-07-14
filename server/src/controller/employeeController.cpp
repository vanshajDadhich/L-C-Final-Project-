#include "../../inc/controller/employeeController.h"

EmployeeController::EmployeeController(std::unique_ptr<MenuItemService> menuItemService,
                                       std::unique_ptr<NextDayMenuVotingService> nextDayMenuVotingService,
                                       std::unique_ptr<FeedbackService> feedbackService,
                                       std::unique_ptr<RecommendationEngine> recommendationEngine,
                                       std::unique_ptr<TodayMenuService> todayMenuService,
                                       std::unique_ptr<NotificationService> notificationService,
                                       std::unique_ptr<UserProfileService> userProfileService,
                                       std::unique_ptr<DiscardMenuItemDetailedFeedbackService> discardMenuItemDetailedFeedbackService)
    : menuItemService(std::move(menuItemService)),
      nextDayMenuVotingService(std::move(nextDayMenuVotingService)),
      feedbackService(std::move(feedbackService)),
      recommendationEngine(std::move(recommendationEngine)),
      todayMenuService(std::move(todayMenuService)),
      notificationService(std::move(notificationService)),
      userProfileService(std::move(userProfileService)),
      discardMenuItemDetailedFeedbackService(std::move(discardMenuItemDetailedFeedbackService)) {}

std::string EmployeeController::handleRequest(Operation operation, const std::string& requestData) {
    std::cout << "[EmployeeController] Handling request: " << static_cast<int>(operation) << "\n";
    std::string response;
    if (operation == Operation::ViewNotification) {
        response = handleViewNotifications();
    } else if (operation == Operation::ProvideFeedback) {
        response = handleProvideFeedback(requestData);
    } else if (operation == Operation::GetTodaysMenu) {
        response = handleGetTodaysMenu();
    } else if (operation == Operation::VoteItemFromTomorrowMenu) {
        response = handleVoteItemFromTomorrowMenu(requestData);
    } else if (operation == Operation::GetChefRollOutMenuForTomorrow) {
        response = handleGetChefRollOutMenuForTomorrow(requestData);
    } else if (operation == Operation::ProvideDiscardMenuItemDetailedFeedback) {
        response = handleProvideDiscardMenuItemDetailedFeedback(requestData);
    }else if(operation == Operation::UpdateProfile){
        response = handleUpdateProfile(requestData);
    } else {
        std::cerr << "[EmployeeController] Invalid operation: " << static_cast<int>(operation) << "\n";
        response = "Invalid operation";
    }
    return response;
}

std::string EmployeeController::handleViewNotifications() {
    std::vector<Notification> notificationDetails = notificationService->getAllNotifications();
    std::vector<std::string> notificationSerializedData;
    for (const auto& notification : notificationDetails) {
        notificationSerializedData.push_back(SerializationUtility::serialize(notification));
    }
    std::cout << "[EmployeeController] View Notifications operation completed\n";
    return SerializationUtility::serializeStringVector(notificationSerializedData);
}

std::string EmployeeController::handleProvideFeedback(const std::string& requestData) {
    std::string response;
    Feedback feedback = SerializationUtility::deserialize<Feedback>(requestData);
    bool operationDone = feedbackService->addFeedback(feedback);
    if (operationDone) {
        std::cout << "[EmployeeController] Feedback Added Successfully\n";
        response = "Feedback Added Successfully";
    } else {
        std::cerr << "[EmployeeController] Failed to Add Feedback\n";
        response = "Failed to Add Feedback";
    }

    return response;
}

std::string EmployeeController::handleGetTodaysMenu() {
    std::vector<MenuItem> todaysMenu = todayMenuService->getAllTodayMenuItem();
    if(todaysMenu.empty()) {
        std::cerr << "[EmployeeController] No menu items for today\n";
        return "0";
    }
    std::vector<std::string> serializedMenuItems;
    for (const auto& menuItem : todaysMenu) {
        serializedMenuItems.push_back(SerializationUtility::serialize(menuItem));
    }
    std::cout << "[EmployeeController] Get Today's Menu operation completed\n";
    return SerializationUtility::serializeStringVector(serializedMenuItems);
}

std::string EmployeeController::handleVoteItemFromTomorrowMenu(const std::string& requestData) {
    std::string response = "";
    int menuItemId;
    try {
        menuItemId = std::stoi(requestData);
    } catch (const std::invalid_argument&) {
        std::cerr << "[EmployeeController] Invalid menu item ID\n";
        response = "Invalid menu item ID";
    }
    bool operationDone = nextDayMenuVotingService->increaseVoteCountForMenuItemId(menuItemId);
    if (operationDone) {
        std::cout << "[EmployeeController] Increased vote count for menu item ID: " << menuItemId << "\n";
        response = "Vote counted successfully";
    } else {
        std::cerr << "[EmployeeController] Failed to increase vote count\n";
        response = "Failed to count vote";
    }

    return response;
}

std::string EmployeeController::handleGetChefRollOutMenuForTomorrow(const std::string& requestData) {
    std::string response;
    int userId;
    try {
        userId = std::stoi(requestData);
    } catch (const std::invalid_argument&) {
        std::cerr << "[EmployeeController] Invalid user ID\n";
        response = "Invalid user ID";
    }
    std::vector<NextDayMenuRollOut> preferenceBasedNextDayMenuRollOut;
    std::vector<NextDayMenuRollOut> chefRolloutMenuForNextDay = getNextDayMenuItemsToRollOut();
    UserProfile userProfile = userProfileService->getUserProfileByID(userId);
    if(userProfile.userId == 0) {
    std::cerr << "[EmployeeController] User profile not found\n";
        return "0";
    }
    if(chefRolloutMenuForNextDay.empty()) {
        std::cerr << "[EmployeeController] No menu items rolled out for the next day\n";
        return "0";
    }
    for (int i = 0; i < 3; ++i) {
        auto chefRollOutMenuForMealType = filterMenuItemsByType(static_cast<MenuItemType>(i + 1), chefRolloutMenuForNextDay);
        chefRollOutMenuForMealType = recommendationEngine->sortRecommendedMenuItemsBasedOnProfile(userProfile, chefRollOutMenuForMealType, menuItemService->getAllMenuItems());
        preferenceBasedNextDayMenuRollOut.insert(preferenceBasedNextDayMenuRollOut.end(), chefRollOutMenuForMealType.begin(), chefRollOutMenuForMealType.end());
    }
    std::vector<std::string> recommendedMenuItemSerializedData;
    for (const auto& menu : preferenceBasedNextDayMenuRollOut) {
        recommendedMenuItemSerializedData.push_back(SerializationUtility::serialize(menu));
    }
    std::cout << "[EmployeeController] Get Chef Rollout Menu for Tomorrow operation completed\n";
    response = SerializationUtility::serializeStringVector(recommendedMenuItemSerializedData);

    return response;
}

std::string EmployeeController::handleProvideDiscardMenuItemDetailedFeedback(const std::string& requestData) {
    std::string response;
    DiscardMenuItemDetailedFeedback feedback = SerializationUtility::deserialize<DiscardMenuItemDetailedFeedback>(requestData);
    bool operationDone = discardMenuItemDetailedFeedbackService->addFeedback(feedback);
    if (operationDone) {
        std::cout << "[EmployeeController] Discard Menu Item Detailed Feedback Added Successfully\n";
        response = "Discard Menu Item Detailed Feedback Added Successfully";
    } else {
        std::cerr << "[EmployeeController] Failed to Add Discard Menu Item Detailed Feedback\n";
        response = "Failed to Add Discard Menu Item Detailed Feedback";
    }
    return response;
}

std::vector<NextDayMenuRollOut> EmployeeController::getNextDayMenuItemsToRollOut() {
    std::vector<NextDayMenuVoting> nextDayMenuVotingList = nextDayMenuVotingService->getAllNextDayMenuRollOutItem();
    std::vector<NextDayMenuRollOut> nextDayMenuRollOutItems = {};

    for (const auto& nextDayMenuItemId : nextDayMenuVotingList) {
        MenuItem menuItem = menuItemService->getMenuItemById(nextDayMenuItemId.menuItemId);

        NextDayMenuRollOut rollOutItem(
            menuItem.menuItemId,
            menuItem.menuItemName,
            menuItem.menuItemType,
            menuItem.price,
            nextDayMenuItemId.voteCount,
            nextDayMenuItemId.rating,
            nextDayMenuItemId.sentiments
        );

        nextDayMenuRollOutItems.push_back(rollOutItem);
    }

    return nextDayMenuRollOutItems;
}

std::vector<NextDayMenuRollOut> EmployeeController::filterMenuItemsByType(MenuItemType menuItemType, const std::vector<NextDayMenuRollOut>& chefRolloutMenuForNextDay) {
    std::vector<NextDayMenuRollOut> filteredMenuItems;
    for (const auto& menuItem : chefRolloutMenuForNextDay) {
        if (menuItem.menuItemType == menuItemType) {
            filteredMenuItems.push_back(menuItem);
        }
    }
    return filteredMenuItems;
}

std::string EmployeeController::handleUpdateProfile(const std::string& requestData) {
    std::string response;
    UserProfile userProfile = SerializationUtility::deserialize<UserProfile>(requestData);
    bool operationDone = userProfileService->updateUserProfile(userProfile);
    if (operationDone) {
        std::cout << "[EmployeeController] Profile Updated Successfully\n";
        response = "Profile Updated Successfully";
    } else {
        std::cerr << "[EmployeeController] Failed to Update Profile\n";
        response = "Failed to Update Profile";
    }

    return response;
}