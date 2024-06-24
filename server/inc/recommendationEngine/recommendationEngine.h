// #pragma once
// #include <iostream>
// #include <vector>
// #include "../service/feedbackService.h"
// #include "../service/menuItemService.h"
// #include "utility.h"
// #include <unordered_set>

// class RecommendationEngine
// {
    
// public:
//     struct MenuItem
//     {
//         std::string name;
//         std::vector<std::string> foodItems;
        
//     };
//         FeedbackService *feedbackService{nullptr};
//         MenuItemService* menuItemService{nullptr};
//         std::unordered_set<std::string> positiveWords_;
//         std::unordered_set<std::string> negativeWords_;
//         std::unordered_set<std::string> negationWords_;
//         RecommendationEngine(FeedbackService *feedbackService, MenuItemService* menuItemService);
//         std::vector<std::string> recommendTopFoodItems();
//         double evaluateFoodItem(const std::string &foodItem);
//         double analyzeSentiment(const std::string &comment);
// };


// #pragma once
// #include <iostream>
// #include <vector>
// #include <unordered_set>
// #include <unordered_map>
// #include "../service/feedbackService.h"
// #include "../service/menuItemService.h"
// #include "utility.h"

// class RecommendationEngine {
// public:
//     enum MenuItemType { Breakfast = 1, Lunch = 2, Dinner = 3 };

//     RecommendationEngine();

//     std::vector<std::string> recommendTopFoodItems(MenuItemType menuType,
//                                                    const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
//                                                    const std::unordered_map<int, MenuItem>& menuItems);

// private:
//     double evaluateFoodItem(const std::vector<Feedback>& feedbacks);
//     double analyzeSentiment(const std::string& comment);

//     std::unordered_set<std::string> positiveWords_;
//     std::unordered_set<std::string> negativeWords_;
//     std::unordered_set<std::string> negationWords_;
// };



#pragma once

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "../service/feedbackService.h"
#include "../service/menuItemService.h"
#include "utility.h"
#include "../DTO/nextDayMenuVoting.h"

class RecommendationEngine {
public:
    RecommendationEngine();

     std::vector<NextDayMenuVoting> recommendTopFoodItems(MenuItemType menuType,
                                                const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
                                                const std::vector<MenuItem>& menuItems);

private:
    double evaluateFoodItem(const std::vector<Feedback>& feedbacks, double& rating, double& sentimentScore);
    double analyzeSentiment(const std::string& comment);

    std::unordered_set<std::string> positiveWords_;
    std::unordered_set<std::string> negativeWords_;
    std::unordered_set<std::string> negationWords_;
};

