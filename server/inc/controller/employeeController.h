#ifndef EMPLOYEECONTROLLER_H
#define EMPLOYEECONTROLLER_H

#include "IUserController.h"
#include "../service/feedbackService.h"
#include "../service/nextDayMenuVotingService.h"
#include "../DTO/nextDayMenuRollout.h"
#include "../service/menuItemService.h"
#include "../service/todayMenuService.h"
#include "../serverProcess/vectorSerializer.h"
#include "../service/notificationService.h"
#include "../service/discardMenuItemDetailedFeedbackService.h"
#include "../service/userProfileService.h"
#include "../recommendationEngine/recommendationEngine.h"

class EmployeeController : public IUserController {
    private :
    FeedbackService* feedbackService;
    NextDayMenuVotingService* nextDayMenuVotingService;
    MenuItemService* menuItemService;
    TodayMenuService* todayMenuService;
    NotificationService* notificationService;
    DiscardMenuItemDetailedFeedbackService* discardMenuItemDetailedFeedbackService;
    UserProfileService* userProfileService;
    RecommendationEngine* recommendationEngine;
    

public:
    EmployeeController(FeedbackService* feedbackService, NextDayMenuVotingService* nextDayMenuVotingService, MenuItemService* menuItemService, TodayMenuService* todayMenuService, NotificationService* notificationService, DiscardMenuItemDetailedFeedbackService* discardMenuItemDetailedFeedbackService, UserProfileService* userProfileService, RecommendationEngine* recommendationEngine);
    std::string handleRequest(Operation operation, std::string request) override;
    std::vector<NextDayMenuRollOut> getNextDayMenuItemsToRollOut();
    std::vector<NextDayMenuRollOut> filterMenuItemsByType(MenuItemType menuItemType,
    const std::vector<NextDayMenuRollOut>& chefRolloutMenuForNextDay);

};

#endif