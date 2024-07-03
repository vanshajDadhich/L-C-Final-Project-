#pragma once
#include "databaseConnection.h"
#include "IDiscardMenuItemDetailedFeedbackDAO.h"
#include <vector>

class DiscardMenuItemDetailedFeedbackDAO : public IDiscardMenuItemDetailedFeedbackDAO{
public:
    DiscardMenuItemDetailedFeedbackDAO();

    int addFeedback(const DiscardMenuItemDetailedFeedback& feedback) override;
    DiscardMenuItemDetailedFeedback getFeedbackByID(const int& id) override;
    std::vector<DiscardMenuItemDetailedFeedback> getAllFeedbacks() override;

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};
