#ifndef FEEDBACK_SERVICE_H
#define FEEDBACK_SERVICE_H
#include"../DAO/IFeedbackDAO.h"

#include<unordered_map>

class FeedbackService {
public:
    FeedbackService(IFeedbackDAO* feedbackDAO);
    bool addFeedback(const Feedback& feedback);
    std::unordered_map<int, std::vector<Feedback>> getAllFeedbacks();
    std::vector<Feedback> getFeedbacksForMenuType(MenuItemType menuItemType);
private:
    IFeedbackDAO* feedbackDAO;
};

#endif // FEEDBACK_SERVICE_H