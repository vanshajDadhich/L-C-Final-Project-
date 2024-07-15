#include "../../inc/recommendationEngine/feedbackAnalyzer.h"
#include <algorithm>

FeedbackAnalyzer::FeedbackAnalyzer()
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

double FeedbackAnalyzer::evaluateFoodItem(const std::vector<Feedback>& feedbacks, double& rating, std::string& sentimentsString) {
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
    sentimentsString = getMostRepetitiveSentiments(sentiments);
    return totalScore;
}

std::string FeedbackAnalyzer::getMostRepetitiveSentiments(const std::vector<std::string>& words) {
    std::unordered_map<std::string, int> wordCount;

    for (const std::string& word : words) {
        wordCount[word]++;
    }

    std::vector<std::pair<std::string, int>> wordFreq(wordCount.begin(), wordCount.end());

    std::sort(wordFreq.begin(), wordFreq.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    std::vector<std::string> topWords;
    int count = 0;
    for (const auto& pair : wordFreq) {
        topWords.push_back(pair.first);
        count++;
        if (count >= 4) break;
    }

    std::string result;
    for (size_t i = 0; i < topWords.size(); ++i) {
        result += topWords[i];
        if (i < topWords.size() - 1) {
            result += ", ";
        }
    }

    return result;
}

double FeedbackAnalyzer::analyzeSentiment(const std::string& comment, std::vector<std::string>& foundSentiments) {
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