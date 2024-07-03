#include "../../inc/service/discardMenuItemDetailedFeedbackService.h"

DiscardMenuItemDetailedFeedbackService::DiscardMenuItemDetailedFeedbackService(std::shared_ptr<IDiscardMenuItemDetailedFeedbackDAO> dao)
    : dao(dao) {}

int DiscardMenuItemDetailedFeedbackService::addFeedback(const DiscardMenuItemDetailedFeedback& feedback) {
    return dao->addFeedback(feedback);
}

DiscardMenuItemDetailedFeedback DiscardMenuItemDetailedFeedbackService::getFeedbackByID(const int& id) {
    return dao->getFeedbackByID(id);
}

std::vector<DiscardMenuItemDetailedFeedback> DiscardMenuItemDetailedFeedbackService::getAllFeedbacks() {
    return dao->getAllFeedbacks();
}
