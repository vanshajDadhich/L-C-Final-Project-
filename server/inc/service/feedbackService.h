#ifndef FEEDBACK_SERVICE_H
#define FEEDBACK_SERVICE_H

#include"../DAO/IFeedbackDAO.h"
#include<unordered_map>
#include<memory>

class FeedbackService {
public:
    FeedbackService(std::unique_ptr<IFeedbackDAO> feedbackDAO);
    bool addFeedback(const Feedback& feedback);
    std::unordered_map<int, std::vector<Feedback>> getAllFeedbacks();
    std::vector<Feedback> getFeedbacksForMenuType(MenuItemType menuItemType);
private:
    std::unique_ptr<IFeedbackDAO> feedbackDAO;
};

#endif