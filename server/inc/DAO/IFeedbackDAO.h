#pragma once

#include "../DTO/feedback.h"
#include "../DTO/menuItem.h"
#include <vector>

class IFeedbackDAO {
public:
  virtual bool addFeedback(const Feedback & feedback) = 0;
  virtual bool updateFeedback(const Feedback& feedback) = 0;
  virtual bool deleteFeedbackByID(int feedbackId) = 0;
  virtual Feedback getFeedbackById(int feedbackId) = 0;
  virtual std::vector<Feedback> getFeedbacksByMenuId(uint64_t menuId) = 0;
  virtual std::vector<Feedback> getAllFeedbacks() = 0;
  virtual std::vector<Feedback> getFeedbacksForMenuType(MenuItemType menuItemType) = 0;
};