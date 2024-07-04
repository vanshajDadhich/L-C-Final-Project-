#ifndef IFEEDBACKDAO_H
#define IFEEDBACKDAO_H

#include "../DTO/feedback.h"
#include "../DTO/menuItem.h"
#include <vector>

class IFeedbackDAO {
public:
  virtual bool addFeedback(const Feedback & feedback) = 0;
  virtual bool deleteFeedbackByID(const int& feedbackId) = 0;
  virtual Feedback getFeedbackById(const int& feedbackId) = 0;
  virtual std::vector<Feedback> getFeedbacksByMenuItemId(const int& menuId) = 0;
  virtual std::vector<Feedback> getAllFeedbacks() = 0;
  virtual std::vector<Feedback> getFeedbacksForMenuType(MenuItemType menuItemType) = 0;
};

#endif