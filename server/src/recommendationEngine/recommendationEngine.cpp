// #include "../../inc/recommendationEngine/recommendationEngine.h"
// #include <queue>

// RecommendationEngine::RecommendationEngine(FeedbackService *feedbackService, MenuItemService* menuItemService) : positiveWords_(Utility::readWordsFromFile("PositiveWords.txt")),
//                                                negativeWords_(Utility::readWordsFromFile("NegativeWords.txt")),
//                                                negationWords_(Utility::readWordsFromFile("NegationWords.txt")),
//                                                feedbackService(feedbackService), menuItemService(menuItemService)
// {}

// std::vector<std::string> RecommendationEngine::recommendTopFoodItems()
// {
//     std::priority_queue<std::pair<double, std::string>> foodItemScores;
//     std::unordered_set<std::string> seenItems;
//     MenuService menuService = MenuService();
//     std::vector<std::string> ids = menuService.getMenuItemIds();
//     std::cout << "ids" << std::endl;
//     for (const auto &id : ids)
//     {
//         if (seenItems.find(id) == seenItems.end())
//         {
//             double score = evaluateFoodItem(id);
//             foodItemScores.push({score, id});
//             std::cout << "ids" << std::endl;
//             seenItems.insert(id);
//         }
//     }
//     std::cout << "ids" << std::endl;
//     std::vector<std::string> topFoodItemIds;
//     while (topFoodItemIds.size() < 4 && !foodItemScores.empty())
//     {
//         topFoodItemIds.push_back(foodItemScores.top().second);
//         foodItemScores.pop();
//     }
//     std::cout << "ids" << std::endl;
//     std::vector<std::string> topFoodItemName;
//     for (std::string itemId : topFoodItemIds)
//     {
//         std::string itemName= menuService.getMenuItemNameFromId(itemId);
//         topFoodItemName.push_back(itemName);
//     }
//     return topFoodItemName;
// }

// double RecommendationEngine::evaluateFoodItem(const std::string &ItemId)
// {
//     double totalScore = 0.0;

//     Feedback *feedback = feedbackService->getItemFeedback(ItemId);
//     double averageSentimentScore = 0.0;

//     // for (const auto &comment : feedback.comments)
//     //     averageSentimentScore += analyzeSentiment(comment);
//     averageSentimentScore += analyzeSentiment(feedback->comment);
//     // averageSentimentScore /= feedbackcomments.size();

//     totalScore = (averageSentimentScore + feedback->rating) / 2.0;

//     return totalScore;
// }

// double RecommendationEngine::analyzeSentiment(const std::string &comment)
// {
//     std::string lowerComment = Utility::toLower(comment);
//     std::vector<std::string> words = Utility::splitWords(lowerComment);

//     int sentimentScore = 0;
//     for (size_t i = 0; i < words.size(); ++i)
//     {
//         std::string word = words[i];
//         bool isNegated = (i > 0 && negationWords_.find(words[i - 1]) != negationWords_.end());

//         if (isNegated && i > 1 && negationWords_.find(words[i - 2]) != negationWords_.end())
//         {
//             isNegated = false;
//         }

//         if (positiveWords_.find(word) != positiveWords_.end())
//         {
//             sentimentScore += isNegated ? -1 : 1;
//         }
//         else if (negativeWords_.find(word) != negativeWords_.end())
//         {
//             sentimentScore += isNegated ? 1 : -1;
//         }
//     }

//     if (sentimentScore > 1)
//     {
//         sentimentScore = 1;
//     }
//     else if (sentimentScore < -1)
//     {
//         sentimentScore = -1;
//     }

//     return ((sentimentScore + 1) / 2) * 5;
// }



// #include "../../inc/recommendationEngine/recommendationEngine.h"
// #include <queue>

// RecommendationEngine::RecommendationEngine()
//     : positiveWords_(Utility::readWordsFromFile("PositiveWords.txt")),
//       negativeWords_(Utility::readWordsFromFile("NegativeWords.txt")),
//       negationWords_(Utility::readWordsFromFile("NegationWords.txt")) {}

// std::vector<std::string> RecommendationEngine::recommendTopFoodItems(
//     MenuItemType menuType,
//     const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
//     const std::unordered_map<int, MenuItem>& menuItems) {

//     std::priority_queue<std::pair<double, int>> foodItemScores;

//     for (const auto& pair : feedbackMap) {
//         int menuItemId = pair.first;
//         if (menuItems.find(menuItemId) != menuItems.end() && menuItems.at(menuItemId).menuItemType == menuType) {
//             double score = evaluateFoodItem(pair.second);
//             foodItemScores.push({score, menuItemId});
//         }
//     }

//     std::vector<std::string> topFoodItemNames;
//     while (topFoodItemNames.size() < 4 && !foodItemScores.empty()) {
//         int menuItemId = foodItemScores.top().second;
//         topFoodItemNames.push_back(menuItems.at(menuItemId).menuItemName);
//         foodItemScores.pop();
//     }

//     return topFoodItemNames;
// }

// double RecommendationEngine::evaluateFoodItem(const std::vector<Feedback>& feedbacks) {
//     double totalScore = 0.0;
//     double averageSentimentScore = 0.0;

//     for (const auto& feedback : feedbacks) {
//         averageSentimentScore += analyzeSentiment(feedback.comment);
//     }

//     averageSentimentScore /= feedbacks.size();

//     double averageRating = 0.0;
//     for (const auto& feedback : feedbacks) {
//         averageRating += feedback.rating;
//     }

//     averageRating /= feedbacks.size();
//     totalScore = (averageSentimentScore + averageRating) / 2.0;

//     return totalScore;
// }

// double RecommendationEngine::analyzeSentiment(const std::string& comment) {
//     std::string lowerComment = Utility::toLower(comment);
//     std::vector<std::string> words = Utility::splitWords(lowerComment);

//     int sentimentScore = 0;
//     for (size_t i = 0; i < words.size(); ++i) {
//         std::string word = words[i];
//         bool isNegated = (i > 0 && negationWords_.find(words[i - 1]) != negationWords_.end());

//         if (isNegated && i > 1 && negationWords_.find(words[i - 2]) != negationWords_.end()) {
//             isNegated = false;
//         }

//         if (positiveWords_.find(word) != positiveWords_.end()) {
//             sentimentScore += isNegated ? -1 : 1;
//         } else if (negativeWords_.find(word) != negativeWords_.end()) {
//             sentimentScore += isNegated ? 1 : -1;
//         }
//     }

//     if (sentimentScore > 1) {
//         sentimentScore = 1;
//     } else if (sentimentScore < -1) {
//         sentimentScore = -1;
//     }

//     return ((sentimentScore + 1) / 2) * 5;
// }



#include "../../inc/recommendationEngine/recommendationEngine.h"
#include <queue>

RecommendationEngine::RecommendationEngine()
    : positiveWords_(Utility::readWordsFromFile("PositiveWords.txt")),
      negativeWords_(Utility::readWordsFromFile("NegativeWords.txt")),
      negationWords_(Utility::readWordsFromFile("NegationWords.txt")) {}

std::vector<NextDayMenuVoting> RecommendationEngine::recommendTopFoodItems(
    MenuItemType menuType,
    const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
    const std::vector<MenuItem>& menuItems) {

    // Use a priority queue with a custom comparator to maintain a max-heap
    auto comp = [](const std::pair<double, NextDayMenuVoting>& a, const std::pair<double, NextDayMenuVoting>& b) {
        return a.first < b.first;
    };
    std::priority_queue<std::pair<double, NextDayMenuVoting>, std::vector<std::pair<double, NextDayMenuVoting>>, decltype(comp)> foodItemScores(comp);

    for (const auto& pair : feedbackMap) {
        int menuItemId = pair.first;

        // Find the MenuItem object corresponding to menuItemId
        auto it = std::find_if(menuItems.begin(), menuItems.end(),
                               [&](const MenuItem& item) { return item.menuItemId == menuItemId; });

        if (it != menuItems.end() && it->menuItemType == menuType) {
            double rating, sentimentScore;
            double score = evaluateFoodItem(pair.second, rating, sentimentScore);
            NextDayMenuVoting nextDayMenuVoting(menuItemId, 0, rating, sentimentScore);
            foodItemScores.push({score, nextDayMenuVoting});
        }
    }

    std::vector<NextDayMenuVoting> topFoodItems;
    while (topFoodItems.size() < 4 && !foodItemScores.empty()) {
        NextDayMenuVoting nextDayMenuVoting = foodItemScores.top().second;
        topFoodItems.push_back(nextDayMenuVoting);
        foodItemScores.pop();
    }

    return topFoodItems;
}

double RecommendationEngine::evaluateFoodItem(const std::vector<Feedback>& feedbacks, double &rating, double &sentimentScore) {
    double totalScore = 0.0;
    double averageSentimentScore = 0.0;

    for (const auto& feedback : feedbacks) {
        averageSentimentScore += analyzeSentiment(feedback.comment);
    }

    averageSentimentScore /= feedbacks.size();

    double averageRating = 0.0;
    for (const auto& feedback : feedbacks) {
        averageRating += feedback.rating;
    }

    averageRating /= feedbacks.size();
    rating = averageRating;
    sentimentScore = averageSentimentScore;
    totalScore = (averageSentimentScore + averageRating) / 2.0;

    return totalScore;
}

double RecommendationEngine::analyzeSentiment(const std::string& comment) {
    std::string lowerComment = Utility::toLower(comment);
    std::vector<std::string> words = Utility::splitWords(lowerComment);

    int sentimentScore = 0;
    for (size_t i = 0; i < words.size(); ++i) {
        std::string word = words[i];
        bool isNegated = (i > 0 && negationWords_.find(words[i - 1]) != negationWords_.end());

        if (isNegated && i > 1 && negationWords_.find(words[i - 2]) != negationWords_.end()) {
            isNegated = false;
        }

        if (positiveWords_.find(word) != positiveWords_.end()) {
            sentimentScore += isNegated ? -1 : 1;
        } else if (negativeWords_.find(word) != negativeWords_.end()) {
            sentimentScore += isNegated ? 1 : -1;
        }
    }

    if (sentimentScore > 1) {
        sentimentScore = 1;
    } else if (sentimentScore < -1) {
        sentimentScore = -1;
    }

    return ((sentimentScore + 1) / 2) * 5;
}
