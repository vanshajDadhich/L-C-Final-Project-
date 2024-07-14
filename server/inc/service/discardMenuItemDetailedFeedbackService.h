#ifndef DISCARD_MENU_ITEM_DETAILED_FEEDBACK_SERVICE_H
#define DISCARD_MENU_ITEM_DETAILED_FEEDBACK_SERVICE_H

#include "../DAO/IDiscardMenuItemDetailedFeedbackDAO.h"
#include <memory>
#include <vector>

class DiscardMenuItemDetailedFeedbackService {
public:
    DiscardMenuItemDetailedFeedbackService(std::unique_ptr<IDiscardMenuItemDetailedFeedbackDAO> dao);

    int addFeedback(const DiscardMenuItemDetailedFeedback& feedback);
    DiscardMenuItemDetailedFeedback getFeedbackById(const int& id);
    std::vector<DiscardMenuItemDetailedFeedback> getAllFeedbacks();

private:
    std::unique_ptr<IDiscardMenuItemDetailedFeedbackDAO> discardMenuItemDetailedFeedbackDAO;
};

#endif