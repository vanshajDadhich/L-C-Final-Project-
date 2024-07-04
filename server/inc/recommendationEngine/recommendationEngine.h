#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "../service/feedbackService.h"
#include "../service/menuItemService.h"
#include "utility.h"
#include "../DTO/nextDayMenuVoting.h"
#include "../DTO/nextDayMenuRollout.h"

class RecommendationEngine {
public:
    RecommendationEngine();

    std::vector<NextDayMenuVoting> recommendTopFoodItems(MenuItemType menuType,
                                                const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
                                                const std::vector<MenuItem>& menuItems);

    std::vector<NextDayMenuVoting> generateDiscardMenuList(
                                    const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
                                    const std::vector<MenuItem>& menuItems);

    std::vector<NextDayMenuRollOut> sortRecommendedMenuItemsBasedOnProfile(
                                            const UserProfile& userProfile, 
                                            const std::vector<NextDayMenuRollOut>& chefRolloutMenuForNextDay, 
                                            const std::vector<MenuItem>& menuItems);
    

private:
    double evaluateFoodItem(const std::vector<Feedback>& feedbacks, double& rating, std::string &sentiments);
    double analyzeSentiment(const std::string& comment, std::vector<std::string>& foundSentiments);
    std::string joinSentiments(const std::vector<std::string> &sentiments);
    std::string getMostRepetativeSentiments(const std::vector<std::string>& words);
    Utility utility_;

    std::unordered_set<std::string> positiveWords_;
    std::unordered_set<std::string> negativeWords_;
    std::unordered_set<std::string> negationWords_;
};

#endif