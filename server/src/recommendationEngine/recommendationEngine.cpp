#include "../../inc/recommendationEngine/recommendationEngine.h"

#include <algorithm>

RecommendationEngine::RecommendationEngine() 
    : feedbackAnalyzer_(std::make_unique<FeedbackAnalyzer>()) {}

std::vector<MenuItem> RecommendationEngine::filterAvailableMenuItems(MenuItemType menuType, const std::vector<MenuItem>& menuItems) {
    std::vector<MenuItem> availableMenuItems;
    for (const auto& item : menuItems) {
        if (item.menuItemType == menuType && item.availability) {
            availableMenuItems.push_back(item);
        }
    }
    return availableMenuItems;
}

std::vector<std::pair<double, NextDayMenuVoting>> RecommendationEngine::scoreMenuItems(
    const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
    const std::vector<MenuItem>& availableMenuItems) {

    std::vector<std::pair<double, NextDayMenuVoting>> foodItemScores;

    for (const auto& pair : feedbackMap) {
        int menuItemId = pair.first;

        auto it = std::find_if(availableMenuItems.begin(), availableMenuItems.end(),
                               [&](const MenuItem& item) { return item.menuItemId == menuItemId; });

        if (it != availableMenuItems.end()) {
            double rating; 
            std::string sentiments;
            double score = feedbackAnalyzer_->evaluateFoodItem(pair.second, rating, sentiments);
            NextDayMenuVoting nextDayMenuVoting(menuItemId, 0, rating, sentiments);
            foodItemScores.push_back({score, nextDayMenuVoting});
        }
    }

    return foodItemScores;
}

std::vector<NextDayMenuVoting> RecommendationEngine::recommendTopFoodItems(
    MenuItemType menuType,
    const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
    const std::vector<MenuItem>& menuItems) {

    auto availableMenuItems = filterAvailableMenuItems(menuType, menuItems);
    auto foodItemScores = scoreMenuItems(feedbackMap, availableMenuItems);

    auto comp = [](const std::pair<double, NextDayMenuVoting>& a, const std::pair<double, NextDayMenuVoting>& b) {
        return a.first < b.first;
    };

    std::priority_queue<std::pair<double, NextDayMenuVoting>, std::vector<std::pair<double, NextDayMenuVoting>>, decltype(comp)> sortedfoodItemScores(comp);

    for(auto foodItemScore : foodItemScores){
        sortedfoodItemScores.push(foodItemScore);
    }

    std::vector<NextDayMenuVoting> topFoodItems;
    while (topFoodItems.size() < 4 && !sortedfoodItemScores.empty()) {
        NextDayMenuVoting nextDayMenuVoting = sortedfoodItemScores.top().second;
        topFoodItems.push_back(nextDayMenuVoting);
        sortedfoodItemScores.pop();
    }

    return topFoodItems;
}

std::vector<NextDayMenuVoting> RecommendationEngine::generateDiscardMenuList(
    const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
    const std::vector<MenuItem>& menuItems) {

    std::vector<NextDayMenuVoting> discardList;

    for (const auto& pair : feedbackMap) {
        int menuItemId = pair.first;

        auto it = std::find_if(menuItems.begin(), menuItems.end(),
                               [&](const MenuItem& item) { return item.menuItemId == menuItemId; });

        if (it != menuItems.end()) {
            double rating;
            std::string sentiments;
            double score = feedbackAnalyzer_->evaluateFoodItem(pair.second, rating, sentiments);
            if (score < 3 && rating < 2) {
                NextDayMenuVoting nextDayMenuVoting(menuItemId, 0, rating, sentiments);
                discardList.push_back(nextDayMenuVoting);
            }
        }
    }

    return discardList;
}

int RecommendationEngine::calculateMatchPreferenceScore(const UserProfile& userProfile, const MenuItem& menuItem) {
    int score = 0;
    if (userProfile.vegetarianPreference == menuItem.vegetarianPreference) score++;
    if (userProfile.spiceLevelOption == menuItem.spiceLevelOption) score++;
    if (userProfile.foodPreference == menuItem.foodPreference) score++;
    if (userProfile.sweetToothPreference == menuItem.sweetToothPreference) score++;
    return score;
}

std::vector<NextDayMenuRollOut> RecommendationEngine::sortRecommendedMenuItemsBasedOnProfile(
    const UserProfile& userProfile, 
    const std::vector<NextDayMenuRollOut>& chefRolloutMenuForNextDay, 
    const std::vector<MenuItem>& menuItems) {

    if (userProfile.userId == 0) {
        return chefRolloutMenuForNextDay;
    }

    std::vector<NextDayMenuRollOut> sortedMenuItems = chefRolloutMenuForNextDay;

    std::sort(sortedMenuItems.begin(), sortedMenuItems.end(), [&](const NextDayMenuRollOut& a, const NextDayMenuRollOut& b) {
        int matchPreferenceScoreA = 0, matchPreferenceScoreB = 0;

        auto itA = std::find_if(menuItems.begin(), menuItems.end(),
                                [&](const MenuItem& item) { return item.menuItemId == a.menuItemId; });
        auto itB = std::find_if(menuItems.begin(), menuItems.end(),
                                [&](const MenuItem& item) { return item.menuItemId == b.menuItemId; });

        if (itA != menuItems.end()) {
            matchPreferenceScoreA = calculateMatchPreferenceScore(userProfile, *itA);
        }

        if (itB != menuItems.end()) {
            matchPreferenceScoreB = calculateMatchPreferenceScore(userProfile, *itB);
        }

        return matchPreferenceScoreA > matchPreferenceScoreB;
    });

    return sortedMenuItems;
}