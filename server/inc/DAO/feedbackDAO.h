#ifndef FEEDBACKDAO_H
#define FEEDBACKDAO_H

#include "IFeedbackDAO.h"
#include <vector>   
#include "databaseConnection.h"

class FeedbackDAO : public IFeedbackDAO {
public:
    FeedbackDAO();

    bool addFeedback(const Feedback& feedback);

    bool updateFeedback(const Feedback& feedback);

    bool deleteFeedbackByID(const int& feedbackId);

    Feedback getFeedbackByID(const int& feedbackId);

    std::vector<Feedback> getFeedbacksByMenuItemId(const int& menuItemId);

    std::vector<Feedback> getAllFeedbacks();

    std::vector<Feedback> getFeedbacksForMenuType(MenuItemType menuItemType) = 0;

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};

#endif