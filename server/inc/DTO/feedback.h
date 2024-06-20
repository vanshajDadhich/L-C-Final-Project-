#pragma once

#include <cstdint>
#include <string>

struct Feedback {
  int feedbackId;
  int userId;
  int menuItemId;
  int rating;
  std::string comment;
  std::string date;

  Feedback(int feedbackId, int userId, int menuItemId, int rating,
           std::string comment, std::string date)
      : feedbackId{feedbackId}, userId{userId}, menuItemId{menuItemId},
        comment{comment}, rating{rating}, date{date} {}

};