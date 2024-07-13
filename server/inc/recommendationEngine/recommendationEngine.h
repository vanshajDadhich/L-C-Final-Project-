#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>

#include "feedbackAnalyzer.h"
#include "../DTO/nextDayMenuVoting.h"
#include "../DTO/nextDayMenuRollout.h"

class RecommendationEngine {
private:
    std::unique_ptr<FeedbackAnalyzer> feedbackAnalyzer_;

    std::vector<MenuItem> filterAvailableMenuItems(MenuItemType menuType, const std::vector<MenuItem>& menuItems);
    std::vector<std::pair<double, NextDayMenuVoting>> scoreMenuItems(
        const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
        const std::vector<MenuItem>& availableMenuItems);
    int calculateMatchPreferenceScore(const UserProfile& userProfile, const MenuItem& menuItem);

public:
    RecommendationEngine();
    std::vector<NextDayMenuVoting> recommendTopFoodItems(
        MenuItemType menuType,
        const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
        const std::vector<MenuItem>& menuItems);
    std::vector<NextDayMenuVoting> generateDiscardMenuList(
        const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
        const std::vector<MenuItem>& menuItems);
    std::vector<NextDayMenuRollOut> sortRecommendedMenuItemsBasedOnProfile(
        const UserProfile& userProfile, 
        const std::vector<NextDayMenuRollOut>& chefRolloutMenuForNextDay, 
        const std::vector<MenuItem>& menuItems);
};

#endif