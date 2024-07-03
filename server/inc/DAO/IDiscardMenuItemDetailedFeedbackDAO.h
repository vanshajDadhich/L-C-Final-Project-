#pragma once
#include "../DTO/discardMenuItemDetailedFeedback.h"
#include <vector>

class IDiscardMenuItemDetailedFeedbackDAO {
public:
    virtual ~IDiscardMenuItemDetailedFeedbackDAO() = default;

    virtual int addFeedback(const DiscardMenuItemDetailedFeedback& feedback) = 0;
    virtual DiscardMenuItemDetailedFeedback getFeedbackByID(const int& id) = 0;
    virtual std::vector<DiscardMenuItemDetailedFeedback> getAllFeedbacks() = 0;
};
