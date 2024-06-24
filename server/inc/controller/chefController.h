#ifndef CHEFCONTROLLER_H
#define CHEFCONTROLLER_H

#include "IUserController.h"
#include "../service/menuItemService.h"
#include "../service/nextDayMenuVotingService.h"
#include "../service/feedbackService.h"
#include "../recommendationEngine/recommendationEngine.h"
#include "../serverProcess/vectorSerializer.h"
#include "../DTO/nextDayMenuRollout.h"

class ChefController : public IUserController {
    private:
       std::vector<NextDayMenuVoting> nextDayMenuRecommendation;
       MenuItemService* menuItemService;
       NextDayMenuVotingService* nextDayMenuVotingService;
       FeedbackService* feedbackService;
       RecommendationEngine * recommendationEngine;
       
    public:
        ChefController(MenuItemService* menuItemService, NextDayMenuVotingService* nextDayMenuVotingService, FeedbackService* feedbackService, RecommendationEngine * recommendationEngine);
        std::string handleRequest(Operation operation, std::string request) override;
        std::vector<NextDayMenuRollOut> getTopMenuRecommendationFromEngine(MenuItemType menuItemType);
        std::vector<NextDayMenuRollOut> getNextDayMenuItemsToRollOut(std::vector<NextDayMenuVoting> nextDayMenuToRollOut);
        bool rollOutFinalMenuByChefForNextDay(std::vector<int> menuItemId);
};

#endif