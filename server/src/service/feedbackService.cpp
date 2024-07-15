#include "../../inc/service/feedbackService.h"
#include <iostream>

FeedbackService::FeedbackService(std::unique_ptr<IFeedbackDAO> feedbackDAO)
    : feedbackDAO(std::move(feedbackDAO)) {}

bool FeedbackService::addFeedback(const Feedback& feedback) {
    return feedbackDAO->addFeedback(feedback);
}

std::unordered_map<int, std::vector<Feedback>> FeedbackService::getAllFeedbacks() {
    std::unordered_map<int, std::vector<Feedback>> feedbackMap;
    std::vector<Feedback> feedbacks = feedbackDAO->getAllFeedbacks();

    for (const auto& feedback : feedbacks) {
        feedbackMap[feedback.menuItemId].push_back(feedback);
    }

    return feedbackMap;
}

std::vector<Feedback> FeedbackService::getFeedbacksForMenuType(MenuItemType menuItemType) {
    return feedbackDAO->getFeedbacksForMenuType(menuItemType);
}