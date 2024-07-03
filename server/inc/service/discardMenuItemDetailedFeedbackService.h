#pragma once
#include "../DTO/discardMenuItemDetailedFeedback.h"
#include "../DAO/IDiscardMenuItemDetailedFeedbackDAO.h"
#include <memory>
#include <vector>

class DiscardMenuItemDetailedFeedbackService {
public:
    DiscardMenuItemDetailedFeedbackService(std::shared_ptr<IDiscardMenuItemDetailedFeedbackDAO> dao);

    int addFeedback(const DiscardMenuItemDetailedFeedback& feedback);
    DiscardMenuItemDetailedFeedback getFeedbackByID(const int& id);
    std::vector<DiscardMenuItemDetailedFeedback> getAllFeedbacks();

private:
    std::shared_ptr<IDiscardMenuItemDetailedFeedbackDAO> dao;
};
