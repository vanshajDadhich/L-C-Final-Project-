#ifndef FEEDBACK_SERVICE_H
#define FEEDBACK_SERVICE_H
#include"../DAO/IFeedbackDAO.h"

class FeedbackService {
public:
    FeedbackService(IFeedbackDAO* feedbackDAO);
    bool addFeedback(const Feedback& feedback);
    std::vector<Feedback> getAllFeedbacks();
    std::vector<Feedback> getFeedbacksForMenuType(MenuItemType menuItemType);
private:
    IFeedbackDAO* feedbackDAO;
};

#endif // FEEDBACK_SERVICE_H