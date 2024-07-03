#ifndef CHEFCONTROLLER_H
#define CHEFCONTROLLER_H

#include "IUserController.h"
#include "../service/menuItemService.h"
#include "../service/nextDayMenuVotingService.h"
#include "../service/feedbackService.h"
#include "../service/todayMenuService.h"
#include "../recommendationEngine/recommendationEngine.h"
#include "../serverProcess/vectorSerializer.h"
#include "../DTO/nextDayMenuRollout.h"
#include "../service/notificationService.h"

class ChefController : public IUserController {
    private:
       std::vector<NextDayMenuVoting> nextDayMenuRecommendation;
       MenuItemService* menuItemService;
       NextDayMenuVotingService* nextDayMenuVotingService;
       FeedbackService* feedbackService;
       RecommendationEngine * recommendationEngine;
       TodayMenuService* todayMenuService;
       NotificationService* notificationService;

    public:
        ChefController(MenuItemService* menuItemService, NextDayMenuVotingService* nextDayMenuVotingService, FeedbackService* feedbackService, RecommendationEngine * recommendationEngine, TodayMenuService* todayMenuService, NotificationService* notificationService);
        std::string handleRequest(Operation operation, std::string request) override;
        std::vector<NextDayMenuRollOut> getTopMenuRecommendationFromEngine(MenuItemType menuItemType);
        std::vector<NextDayMenuRollOut> getNextDayMenuItemsToRollOut(std::vector<NextDayMenuVoting> nextDayMenuToRollOut);
        bool rollOutFinalMenuByChefForNextDay(std::vector<int> menuItemId);
        bool publishMostVotedMenuItems();
        bool pushNotification(Operation operation, std::string message);
};

#endif