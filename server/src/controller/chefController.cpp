#include "../../inc/controller/chefController.h"

ChefController::ChefController(std::unique_ptr<MenuItemService> menuItemService,
                               std::unique_ptr<NextDayMenuVotingService> nextDayMenuVotingService,
                               std::unique_ptr<FeedbackService> feedbackService,
                               std::unique_ptr<RecommendationEngine> recommendationEngine,
                               std::unique_ptr<TodayMenuService> todayMenuService,
                               std::unique_ptr<NotificationService> notificationService)
    : menuItemService(std::move(menuItemService)), nextDayMenuVotingService(std::move(nextDayMenuVotingService)),
      feedbackService(std::move(feedbackService)), recommendationEngine(std::move(recommendationEngine)),
      todayMenuService(std::move(todayMenuService)), notificationService(std::move(notificationService)) {}

std::string ChefController::handleRequest(Operation operation, const std::string& requestData) {
    std::cout << "[ChefController] Handling request: " << static_cast<int>(operation) << "\n";
    std::string response;

    if (operation == Operation::ViewMenu) {
        response = handleViewMenu();
    } else if (operation == Operation::RollOutMenuForNextDay) {
        response = handleRollOutMenuForNextDay(requestData);
    } else if (operation == Operation::GetRecommandationFromEngine) {
        response = handleGetRecommendationFromEngine(requestData);
    } else if (operation == Operation::PublishMenuForToday) {
        response = handlePublishMenuForToday();
    } else if (operation == Operation::GetDiscardMenuList) {
        response = handleGetDiscardMenuList();
    } else if (operation == Operation::RemoveMenuItemFromList) {
        response = handleRemoveMenuItemFromList(requestData);
    } else if (operation == Operation::GetMenuItemIdForDetailFeedbackFromChef) {
        response = handleGetMenuItemIdForDetailFeedbackFromChef(requestData);
    } else if (operation == Operation::GetNextDayMenuVoting) {
        response = handleGetNextDayMenuVoting();
    } else {
        std::cerr << "[ChefController] Invalid operation: " << static_cast<int>(operation) << "\n";
        response = "Invalid operation";
    }

    return response;
}

std::string ChefController::handleGetNextDayMenuVoting() {
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

    std::vector<std::string> nextDayMenuVotingSerializedData;
    for (const auto& menu : nextDayMenuRollOutItems) {
        nextDayMenuVotingSerializedData.push_back(SerializationUtility::serialize(menu));
    }
    std::cout << "[ChefController] Next Day Menu Voting operation completed\n";
    return SerializationUtility::serializeStringVector(nextDayMenuVotingSerializedData);
}

std::string ChefController::handleViewMenu() {
    std::vector<MenuItem> menuDetails = menuItemService->getAllMenuItems();
    std::vector<std::string> menuSerializedData;
    for (const auto& menu : menuDetails) {
        menuSerializedData.push_back(SerializationUtility::serialize(menu));
    }
    std::cout << "[ChefController] View Menu operation completed\n";
    return SerializationUtility::serializeStringVector(menuSerializedData);
}

std::string ChefController::handleRollOutMenuForNextDay(const std::string& requestData) {
    std::string response;
    std::cout << "[ChefController] RollOutMenuForNextDay called\n";
    std::vector<std::string> menuItemIdToRollOutMenu = SerializationUtility::deserializeStringToVector(requestData);
    std::vector<int> menuItemIdsForNextDayMenu;
    for (const auto& menuItemForMenuType : menuItemIdToRollOutMenu) {
        std::vector<std::string> menuItemIds = SerializationUtility::deserializeStringToVector(menuItemForMenuType, ',');
        for (const auto& menuItemId : menuItemIds) {
            menuItemIdsForNextDayMenu.push_back(std::stoi(menuItemId));
        }
    }
    bool operationDone = rollOutFinalMenuByChefForNextDay(menuItemIdsForNextDayMenu);
    if (operationDone) {
        pushNotification(Operation::RollOutMenuForNextDay, "Menu rolled out successfully for next day");
        response = "Menu rolled out successfully for next day";
    } else {
        response = "Failed to roll out menu for next day";
    }

    return response;
}

std::string ChefController::handleGetRecommendationFromEngine(const std::string& requestData) {
    std::vector<NextDayMenuRollOut> recommendedMenuItem = getTopMenuRecommendationFromEngine(static_cast<MenuItemType>(std::stoi(requestData)));
    std::vector<std::string> recommendedMenuItemSerializedData;
    for (const auto& menu : recommendedMenuItem) {
        recommendedMenuItemSerializedData.push_back(SerializationUtility::serialize(menu));
    }
    std::cout << "[ChefController] Recommended Menu from Engine operation completed\n";
    return SerializationUtility::serializeStringVector(recommendedMenuItemSerializedData);
}

std::string ChefController::handlePublishMenuForToday() {
    std::string response;
    std::vector<int> publishedMenuItemIds = publishMostVotedMenuItems();
    if (publishedMenuItemIds.size() > 0){
        std::vector<MenuItem> todaysMenuPublished = {};
        for(const auto& menuItemId : publishedMenuItemIds) {
            todaysMenuPublished.push_back(menuItemService->getMenuItemById(menuItemId));
        }

        std::vector<std::string> todaysMenuSerializedData;
        for (const auto& menu : todaysMenuPublished) {
            todaysMenuSerializedData.push_back(SerializationUtility::serialize(menu));
        }

        std::string serializedTodaysMenu = SerializationUtility::serializeStringVector(todaysMenuSerializedData);
        
        pushNotification(Operation::PublishMenuForToday, "Today's menu has been published");
        response = serializedTodaysMenu;
    } else {
        response = "Failed to publish today's menu";
    }

    return response;
}

std::string ChefController::handleGetDiscardMenuList() {
    std::unordered_map<int, std::vector<Feedback>> feedbackMap = feedbackService->getAllFeedbacks();
    std::vector<MenuItem> menuItems = menuItemService->getAllMenuItems();
    std::vector<NextDayMenuVoting> discardMenuList = recommendationEngine->generateDiscardMenuList(feedbackMap, menuItems);
    std::vector<NextDayMenuRollOut> discardedMenuItemList = getNextDayMenuItemsToRollOut(discardMenuList);
    std::vector<std::string> discardMenuSerializedData;
    for (const auto& menu : discardedMenuItemList) {
        discardMenuSerializedData.push_back(SerializationUtility::serialize(menu));
    }
    std::cout << "[ChefController] Discard Menu List operation completed\n";
    return SerializationUtility::serializeStringVector(discardMenuSerializedData);
}

std::string ChefController::handleRemoveMenuItemFromList(const std::string& requestData) {
    std::string response;
    MenuItem menuItem = menuItemService->deleteMenuItemById(std::stoi(requestData));
    if (menuItem.menuItemId != 0) {
        pushNotification(Operation::DeleteMenuItem, menuItem.menuItemName);
        response = "Menu Item Deleted Successfully";
    } else {
        response = "Menu Item Not Deleted";
    }
    return response;
}

std::string ChefController::handleGetMenuItemIdForDetailFeedbackFromChef(const std::string& requestData) {
    pushNotification(Operation::GetMenuItemIdForDetailFeedbackFromChef, requestData);
    return "Notification Sent to User for Detailed Feedback";
}

std::vector<NextDayMenuRollOut> ChefController::getTopMenuRecommendationFromEngine(MenuItemType menuItemType) {
    std::cout << "[ChefController] Inside getTopMenuRecommendationFromEngine\n";
    std::unordered_map<int, std::vector<Feedback>> feedbackMap = feedbackService->getAllFeedbacks();
    std::vector<MenuItem> menuItems = menuItemService->getAllMenuItems();
    std::vector<NextDayMenuVoting> nextDayMenuRecommendationForMenuType = recommendationEngine->recommendTopFoodItems(menuItemType, feedbackMap, menuItems);
    nextDayMenuRecommendation.insert(nextDayMenuRecommendation.end(),
                                     nextDayMenuRecommendationForMenuType.begin(),
                                     nextDayMenuRecommendationForMenuType.end());
    return getNextDayMenuItemsToRollOut(nextDayMenuRecommendationForMenuType);
}

std::vector<NextDayMenuRollOut> ChefController::getNextDayMenuItemsToRollOut(const std::vector<NextDayMenuVoting>& nextDayMenuToRollOut) {
    std::vector<NextDayMenuRollOut> nextDayMenuRollOutItems;

    for (const auto& nextDayMenuItemId : nextDayMenuToRollOut) {
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

bool ChefController::rollOutFinalMenuByChefForNextDay(const std::vector<int>& menuItemIds) {
    std::cout << "[ChefController] rollOutFinalMenuByChefForNextDay: entry\n";
    std::vector<NextDayMenuVoting> finalChefMenuForNextDay;

    for (const auto& menuId : menuItemIds) {
        auto it = std::find_if(nextDayMenuRecommendation.begin(), nextDayMenuRecommendation.end(),
                               [&menuId](const NextDayMenuVoting& voting) {
                                   return voting.menuItemId == menuId;
                               });

        if (it != nextDayMenuRecommendation.end()) {
            finalChefMenuForNextDay.push_back(*it);
        } else {
            std::cout << "[ChefController] Item not found in Recommendation Engine suggestion\n";
        }
    }

    std::cout << "[ChefController] Adding recommended menu data into table by chef\n";
    nextDayMenuVotingService->deleteMenuRolledOut();
    bool operationDone = nextDayMenuVotingService->addNextDayMenuRollout(finalChefMenuForNextDay);
    nextDayMenuRecommendation.clear();
    return operationDone;
}

std::vector<int> ChefController::publishMostVotedMenuItems() {
    std::vector<int> mostVotedMenuItemIds = nextDayMenuVotingService->getMostVotedMenuItemIds();
    todayMenuService->deleteTodayMenu();
    bool publishedTodaysMenu =  todayMenuService->addTodayMenu(mostVotedMenuItemIds);
    if(publishedTodaysMenu) {
        nextDayMenuVotingService->deleteMenuRolledOut();
        return mostVotedMenuItemIds;
    }
    return {};
}

bool ChefController::pushNotification(Operation operation, const std::string& message) {
    Notification notification;
    if (operation == Operation::PublishMenuForToday) {
        notification.notificationTitle = "Today's Menu Published";
        notification.message = "Today's menu has been published.";
    } else if (operation == Operation::RollOutMenuForNextDay) {
        notification.notificationTitle = "Menu Rollout For Next Day";
        notification.message = "Chef has rolled out the menu items for the next day. Check it out in the User Menu.";
    } else if (operation == Operation::DeleteMenuItem) {
        notification.notificationTitle = "Menu Item Deleted";
        notification.message = message + " has been deleted from the menu.";
    } else if (operation == Operation::GetMenuItemIdForDetailFeedbackFromChef) {
        notification.notificationTitle = "Feedback for Discarded Menu Item";
        notification.message = "Menu Item ID: " + message + " has low ratings and bad comments. Please share detailed feedback on this menu item.";
    } else {
        return false;
    }
    return notificationService->addNotification(notification);
}
