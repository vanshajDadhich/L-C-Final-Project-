#include "../../inc/recommendationEngine/recommendationEngine.h"
#include <queue>


RecommendationEngine::RecommendationEngine()
    // : positiveWords_(Utility::readWordsFromFile("PositiveWords.txt")),
    //   negativeWords_(Utility::readWordsFromFile("NegativeWords.txt")),
    //   negationWords_(Utility::readWordsFromFile("NegationWords.txt")) 
{
    negationWords_ = {
    "not", "never", "no", "none", "nothing", "nowhere", "neither", "hardly", "scarcely",
    "barely", "without", "seldom", "rarely", "cannot", "can't", "doesn't", "don't", "isn't",
    "wasn't", "weren't", "won't", "wouldn't", "shouldn't", "mustn't", "mightn't", "didn't",
    "hasn't", "hadn't", "haven't", "ain't", "non", "nobody", "nor", "zero", "absolutely",
    "neglect", "omit", "absent", "disallow", "forbid", "prevent", "prohibit", "refuse",
    "decline", "ban", "exclude", "block", "disagree", "reject", "void", "cancel", "nullify",
    "abandon", "ignore", "expected", "but","too", "under", "over", "lacked"
    };

    negativeWords_ = {
    "bad", "terrible", "horrible", "awful", "hate", "disgusting", "poor", "negative",
    "sad", "unhappy", "miserable", "displeased", "dissatisfied", "horrendous", "dreadful",
    "atrocious", "lousy", "pathetic", "abysmal", "disappointing", "wretched", "unpleasant",
    "horrific", "lamentable", "subpar", "inferior", "unacceptable", "criticize", "condemn",
    "regretful", "terrifying", "depressing", "disturbing", "frustrating", "annoying", 
    "offensive", "nasty", "vulgar", "appalling", "sickening", "dreaded", "ghastly",
    "detestable", "despicable", "loathsome", "grim", "unfortunate", "distasteful", 
    "dismal", "gloomy", "grief", "cold", "bland", "too", "oily", "dry", "tasteless", 
    "nothing", "overcooked", "undercooked", "tough", "under", "over", "lacked", "expected", 
    "nothing", "mediocre", "needed", "more", "okay", "bland", "nothing special", 
    "too spicy", "more seasoning", "too tough", "not very fresh", "too oily", "too salty",
    "average", "underwhelming", "too sweet"
    };

    positiveWords_ = {
    "good", "great", "excellent", "amazing", "fantastic", "love", "nice", "wonderful",
    "brilliant", "superb", "fabulous", "positive", "happy", "joyful", "delightful",
    "pleased", "satisfied", "awesome", "terrific", "splendid", "magnificent",
    "outstanding", "impressive", "charming", "graceful", "admire", "commendable",
    "remarkable", "pleasing", "incredible", "beautiful", "marvelous", "delicious",
    "refreshing", "perfect", "elegant", "thrilling", "enthusiastic", "radiant",
    "vibrant", "spectacular", "prosperous", "generous", "supportive", "favorable",
    "delight", "glorious", "blissful", "enchanting", "admirable", "exciting",
    "enjoyable", "uplifting", "cheerful", "fantastic", "flavorful", "loved", "amazing", 
    "delicious", "tender", "recommend", "well-cooked", "rich", "juicy", "soft", "heavenly", 
    "fresh", "outstanding", "superb", "moist", "highly", "divine", "perfectly", "crispy", 
    "very", "excellent", "best", "pretty", "fluffy", "very tasty", "perfectly cooked", 
    "highly recommend", "well cooked", "just right", "well-cooked", "fresh and tasty",
    "great maple syrup", "right amount of spice", "loved it", "superb", "well-cooked", 
    "amazing", "refreshing", "perfectly sweet", "delightful", "delicious", "fantastic",
    "fresh and delicious", "absolutely loved", "fluffy", "fresh and refreshing"
    };
}

std::vector<NextDayMenuVoting> RecommendationEngine::recommendTopFoodItems(
    MenuItemType menuType,
    const std::unordered_map<int, std::vector<Feedback>>& feedbackMap,
    const std::vector<MenuItem>& menuItems) {

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
            double rating; 
            std::string sentiments;
            double score = evaluateFoodItem(pair.second, rating, sentiments);
            NextDayMenuVoting nextDayMenuVoting(menuItemId, 0, rating, sentiments);
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

std::string RecommendationEngine::getMostRepetativeSentiments(const std::vector<std::string>& words) {
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

    // Join top 4 words into a comma-separated string
    std::string result;
    for (size_t i = 0; i < topWords.size(); ++i) {
        result += topWords[i];
        if (i < topWords.size() - 1) {
            result += ", ";
        }
    }

    return result;
}


double RecommendationEngine::evaluateFoodItem(const std::vector<Feedback>& feedbacks, double &rating, std::string &sentimentsString) {
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
    totalScore = (averageSentimentScore + averageRating) / 2.0;
    sentimentsString = getMostRepetativeSentiments(sentiments);
    std::cout<<"sentimentsString : "<<sentimentsString<<std::endl;
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
            double rating;
            std::string sentiments;
            double score = evaluateFoodItem(pair.second, rating, sentiments);
            std::cout<<"menuItemId : "<<menuItemId<<" score : "<<score<<" rating : "<<rating<<" sentiments : "<<sentiments<<std::endl;
            if (score < 4 && rating < 4) {
                NextDayMenuVoting nextDayMenuVoting(menuItemId, 0, rating, sentiments);
                discardList.push_back(nextDayMenuVoting);
                std::cout<<"pushing list in it discard Menu list"<<std::endl;
            }
        }
    }

    return discardList;
}


