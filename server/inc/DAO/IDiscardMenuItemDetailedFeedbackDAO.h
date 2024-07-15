#ifndef IDISCARDMENUITEMDETAILEDFEEDBACKDAO_H
#define IDISCARDMENUITEMDETAILEDFEEDBACKDAO_H

#include "../../../common/DTO/discardMenuItemDetailedFeedback.h"
#include <vector>

class IDiscardMenuItemDetailedFeedbackDAO {
public:
    virtual ~IDiscardMenuItemDetailedFeedbackDAO() = default;

    virtual int addFeedback(const DiscardMenuItemDetailedFeedback& feedback) = 0;
    virtual DiscardMenuItemDetailedFeedback getFeedbackById(const int& id) = 0;
    virtual std::vector<DiscardMenuItemDetailedFeedback> getAllFeedbacks() = 0;
};

#endif