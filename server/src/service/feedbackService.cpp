#include "../../inc/service/feedbackService.h"
#include <iostream>

FeedbackService::FeedbackService(IFeedbackDAO* feedbackDAO)
    : feedbackDAO(feedbackDAO) {}

bool FeedbackService::addFeedback(const Feedback& feedback) {
    return feedbackDAO->addFeedback(feedback);
}

std::vector<Feedback> FeedbackService::getAllFeedbacks() {
    return feedbackDAO->getAllFeedbacks();
}

std::vector<Feedback> FeedbackService::getFeedbacksForMenuType(MenuItemType menuItemType) {
    return feedbackDAO->getFeedbacksForMenuType(menuItemType);
}