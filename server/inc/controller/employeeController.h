#ifndef EMPLOYEECONTROLLER_H
#define EMPLOYEECONTROLLER_H

#include "IUserController.h"
#include "../service/feedbackService.h"
#include "../service/nextDayMenuVotingService.h"
#include "../DTO/nextDayMenuRollout.h"
#include "../service/menuItemService.h"
#include "../service/todayMenuService.h"
#include "../service/notificationService.h"
#include "../service/discardMenuItemDetailedFeedbackService.h"
#include "../service/userProfileService.h"
#include "../recommendationEngine/recommendationEngine.h"

class EmployeeController : public IUserController {
private:
    std::unique_ptr<MenuItemService> menuItemService;
    std::unique_ptr<NextDayMenuVotingService> nextDayMenuVotingService;
    std::unique_ptr<FeedbackService> feedbackService;
    std::unique_ptr<RecommendationEngine> recommendationEngine;
    std::unique_ptr<TodayMenuService> todayMenuService;
    std::unique_ptr<NotificationService> notificationService;
    std::unique_ptr<UserProfileService> userProfileService;
    std::unique_ptr<DiscardMenuItemDetailedFeedbackService> discardMenuItemDetailedFeedbackService;

    std::string handleViewNotifications();
    std::string handleProvideFeedback(const std::string& requestData);
    std::string handleGetTodaysMenu();
    std::string handleVoteItemFromTomorrowMenu(const std::string& requestData);
    std::string handleGetChefRollOutMenuForTomorrow(const std::string& requestData);
    std::string handleProvideDiscardMenuItemDetailedFeedback(const std::string& requestData);
    bool pushNotification(Operation operation, const std::string& message);

    std::vector<NextDayMenuRollOut> getNextDayMenuItemsToRollOut();
    std::vector<NextDayMenuRollOut> filterMenuItemsByType(MenuItemType menuItemType, const std::vector<NextDayMenuRollOut>& chefRolloutMenuForNextDay);

public:
    EmployeeController(std::unique_ptr<MenuItemService> menuItemService,
                       std::unique_ptr<NextDayMenuVotingService> nextDayMenuVotingService,
                       std::unique_ptr<FeedbackService> feedbackService,
                       std::unique_ptr<RecommendationEngine> recommendationEngine,
                       std::unique_ptr<TodayMenuService> todayMenuService,
                       std::unique_ptr<NotificationService> notificationService,
                       std::unique_ptr<UserProfileService> userProfileService,
                       std::unique_ptr<DiscardMenuItemDetailedFeedbackService> discardMenuItemDetailedFeedbackService);
    
    std::string handleRequest(Operation operation, const std::string& request) override;
};

#endif
