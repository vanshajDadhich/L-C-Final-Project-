#ifndef FEEDBACKDAO_H
#define FEEDBACKDAO_H

#include <vector>
#include "IFeedbackDAO.h"
#include "databaseConnection.h"

class FeedbackDAO : public IFeedbackDAO {
public:
    FeedbackDAO();

    bool addFeedback(const Feedback& feedback) override;
    bool deleteFeedbackByID(const int& feedbackId) override;
    Feedback getFeedbackById(const int& feedbackId) override;
    std::vector<Feedback> getFeedbacksByMenuItemId(const int& menuItemId) override;
    std::vector<Feedback> getAllFeedbacks() override;
    std::vector<Feedback> getFeedbacksForMenuType(MenuItemType menuItemType) override;

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};

#endif
