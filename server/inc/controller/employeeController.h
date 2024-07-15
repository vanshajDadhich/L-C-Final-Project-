#ifndef EMPLOYEECONTROLLER_H
#define EMPLOYEECONTROLLER_H

#include "IUserController.h"
#include "../../../common/DTO/nextDayMenuRollout.h"
#include "../recommendationEngine/recommendationEngine.h"

class EmployeeController : public IUserController {
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
    std::string handleUpdateProfile(const std::string& requestData);
    std::vector<NextDayMenuRollOut> getNextDayMenuItemsToRollOut();
    template <typename T>
    std::vector<T> filterMenuItemsByType(MenuItemType menuItemType, const std::vector<T>& menuItems);
};

#endif
