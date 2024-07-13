#ifndef FEEDBACK_ANALYZER_H
#define FEEDBACK_ANALYZER_H

#include <unordered_set>
#include <vector>
#include <string>
#include "utility.h"
#include "../DTO/menuItem.h"
#include "../DTO/feedback.h"

class FeedbackAnalyzer {
private:
    std::unordered_set<std::string> positiveWords_;
    std::unordered_set<std::string> negativeWords_;
    std::unordered_set<std::string> negationWords_;
    Utility utility_;

    double analyzeSentiment(const std::string& comment, std::vector<std::string>& foundSentiments);
    std::string getMostRepetitiveSentiments(const std::vector<std::string>& words);

public:
    FeedbackAnalyzer();
    double evaluateFoodItem(const std::vector<Feedback>& feedbacks, double& rating, std::string& sentimentsString);
};

#endif
