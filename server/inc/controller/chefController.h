#ifndef CHEFCONTROLLER_H
#define CHEFCONTROLLER_H

#include "IUserController.h"
#include "../recommendationEngine/recommendationEngine.h"
#include "../../../common/DTO/nextDayMenuRollout.h"

class ChefController : public IUserController {
public:
    ChefController(std::unique_ptr<MenuItemService> menuItemService,
                   std::unique_ptr<NextDayMenuVotingService> nextDayMenuVotingService,
                   std::unique_ptr<FeedbackService> feedbackService,
                   std::unique_ptr<RecommendationEngine> recommendationEngine,
                   std::unique_ptr<TodayMenuService> todayMenuService,
                   std::unique_ptr<NotificationService> notificationService);
    
    std::string handleRequest(Operation operation, const std::string& request) override;

private:
    std::vector<NextDayMenuVoting> nextDayMenuRecommendation;
    std::unique_ptr<MenuItemService> menuItemService;
    std::unique_ptr<NextDayMenuVotingService> nextDayMenuVotingService;
    std::unique_ptr<FeedbackService> feedbackService;
    std::unique_ptr<TodayMenuService> todayMenuService;
    std::unique_ptr<NotificationService> notificationService;

    std::unique_ptr<RecommendationEngine> recommendationEngine;

    std::string handleViewMenu();
    std::string handleRollOutMenuForNextDay(const std::string& requestData);
    std::string handleGetRecommendationFromEngine(const std::string& requestData);
    std::string handlePublishMenuForToday();
    std::string handleGetDiscardMenuList();
    std::string handleGetNextDayMenuVoting();
    std::string handleRemoveMenuItemFromList(const std::string& requestData);
    std::string handleGetMenuItemIdForDetailFeedbackFromChef(const std::string& requestData);
    std::vector<NextDayMenuRollOut> getTopMenuRecommendationFromEngine(MenuItemType menuItemType);
    std::vector<NextDayMenuRollOut> getNextDayMenuItemsToRollOut(const std::vector<NextDayMenuVoting>& nextDayMenuToRollOut);
    bool rollOutFinalMenuByChefForNextDay(const std::vector<int>& menuItemIds);
    std::vector<int> publishMostVotedMenuItems();
    bool pushNotification(Operation operation, const std::string& message);
};

#endif
