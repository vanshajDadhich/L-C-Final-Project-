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


        //recommend only available food Items : assumption that avaiablity of items for tomorrow will be updated today only by admin.

        if (it != menuItems.end() && it->menuItemType == menuType && it->availability) {
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

std::vector<std::string> RecommendationEngine::getMostRepetativeSentiments(const std::vector<std::string>& words) {
    std::unordered_map<std::string, int> wordCount;

    // Count occurrences of each word
    for (const std::string& word : words) {
        wordCount[word]++;
    }

    // Create a vector of pairs (word, count) from the map
    std::vector<std::pair<std::string, int>> wordFreq(wordCount.begin(), wordCount.end());

    // Sort the vector based on count (in descending order)
    std::sort(wordFreq.begin(), wordFreq.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Extract top 4 words
    std::vector<std::string> topWords;
    int count = 0;
    for (const auto& pair : wordFreq) {
        topWords.push_back(pair.first);
        count++;
        if (count >= 4) break;
    }

    return topWords;
}


double RecommendationEngine::evaluateFoodItem(const std::vector<Feedback>& feedbacks, double &rating, double &sentimentScore) {
    double totalScore = 0.0;
    double averageSentimentScore = 0.0;
    std::vector<std::string> sentiments;

    for (const auto& feedback : feedbacks) {
        averageSentimentScore += analyzeSentiment(feedback.comment, sentiments);
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

    for (const std::string& sentiment : sentiments) {
        std::cout <<"Vansh 123 "<< sentiment << std::endl;
    }
    sentiments = getMostRepetativeSentiments(sentiments);
    std::cout<<"Vanshaj Dadhich "<<totalScore<<std::endl;
    for (const std::string& sentiment : sentiments) {
        std::cout <<"Vanshu "<< sentiment << std::endl;
    }

    return totalScore;
}

double RecommendationEngine::analyzeSentiment(const std::string& comment, std::vector<std::string>& foundSentiments) {
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
            foundSentiments.push_back(isNegated ? words[i - 1] + " " + word : word);
        } else if (negativeWords_.find(word) != negativeWords_.end()) {
            sentimentScore += isNegated ? 1 : -1;
            foundSentiments.push_back(isNegated ? words[i - 1] + " " + word : word);
        }
    }

    for (const std::string& sentiment : foundSentiments) {
        std::cout <<"Vansh inside analyze sentiment "<< sentiment << std::endl;
    }


    

    if (sentimentScore > 1) {
        sentimentScore = 1;
    } else if (sentimentScore < -1) {
        sentimentScore = -1;
    }

    return ((sentimentScore + 1) / 2) * 5;
}

std::vector<NextDayMenuVoting> RecommendationEngine::generateDiscardMenuList(
    const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
    const std::vector<MenuItem>& menuItems) {

    std::vector<NextDayMenuVoting> discardList;

    for (const auto& pair : feedbackMap) {
        int menuItemId = pair.first;

        // Find the MenuItem object corresponding to menuItemId
        auto it = std::find_if(menuItems.begin(), menuItems.end(),
                               [&](const MenuItem& item) { return item.menuItemId == menuItemId; });

        if (it != menuItems.end()) {
            double rating, sentimentScore;
            double score = evaluateFoodItem(pair.second, rating, sentimentScore);

            if (rating < 2 || sentimentScore < 2) {
                NextDayMenuVoting nextDayMenuVoting(menuItemId, 0, rating, sentimentScore);
                discardList.push_back(nextDayMenuVoting);
            }
        }
    }

    return discardList;
}