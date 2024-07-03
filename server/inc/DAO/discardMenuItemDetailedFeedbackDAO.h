#pragma once
#include "databaseConnection.h"
#include "../DTO/discardMenuItemDetailedFeedback.h"
#include <vector>

class DiscardMenuItemDetailedFeedbackDAO {
public:
    DiscardMenuItemDetailedFeedbackDAO();

    int addFeedback(const DiscardMenuItemDetailedFeedback& feedback);
    DiscardMenuItemDetailedFeedback getFeedbackByID(const int& id);
    std::vector<DiscardMenuItemDetailedFeedback> getAllFeedbacks();

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};
