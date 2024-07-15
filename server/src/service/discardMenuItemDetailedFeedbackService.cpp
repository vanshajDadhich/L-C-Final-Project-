#include "../../inc/service/discardMenuItemDetailedFeedbackService.h"

DiscardMenuItemDetailedFeedbackService::DiscardMenuItemDetailedFeedbackService(std::unique_ptr<IDiscardMenuItemDetailedFeedbackDAO> discardMenuItemDetailedFeedbackDAO)
    : discardMenuItemDetailedFeedbackDAO(std::move(discardMenuItemDetailedFeedbackDAO)) {}

int DiscardMenuItemDetailedFeedbackService::addFeedback(const DiscardMenuItemDetailedFeedback& feedback) {
    return discardMenuItemDetailedFeedbackDAO->addFeedback(feedback);
}

DiscardMenuItemDetailedFeedback DiscardMenuItemDetailedFeedbackService::getFeedbackById(const int& id) {
    return discardMenuItemDetailedFeedbackDAO->getFeedbackById(id);
}

std::vector<DiscardMenuItemDetailedFeedback> DiscardMenuItemDetailedFeedbackService::getAllFeedbacks() {
    return discardMenuItemDetailedFeedbackDAO->getAllFeedbacks();
}
