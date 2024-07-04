#ifndef DISCARDMENUITEMDETAILEDFEEDBACKDAO_H
#define DISCARDMENUITEMDETAILEDFEEDBACKDAO_H

#include "databaseConnection.h"
#include "IDiscardMenuItemDetailedFeedbackDAO.h"
#include <vector>

class DiscardMenuItemDetailedFeedbackDAO : public IDiscardMenuItemDetailedFeedbackDAO{
public:
    DiscardMenuItemDetailedFeedbackDAO();

    int addFeedback(const DiscardMenuItemDetailedFeedback& feedback) override;
    DiscardMenuItemDetailedFeedback getFeedbackById(const int& id) override;
    std::vector<DiscardMenuItemDetailedFeedback> getAllFeedbacks() override;

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};

#endif
