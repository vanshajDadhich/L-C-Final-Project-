#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include "serializable.h"

struct Feedback : public Serializable {
  int feedbackId;
  int userId;
  int menuItemId;
  int rating;
  std::string comment;
  std::string date;

  Feedback(int feedbackId = 0, int userId = 0, int menuItemId = 0, int rating = 0,
           std::string comment = "", std::string date = "")
      : feedbackId{feedbackId}, userId{userId}, menuItemId{menuItemId},
        rating{rating}, comment{comment}, date{date} {}


  Feedback(){}

  std::string serialize() const override {
    return std::to_string(feedbackId) + ";" +
           std::to_string(userId) + ";" +
           std::to_string(menuItemId) + ";" +
           std::to_string(rating) + ";" +
           comment + ";" +
           date;
  }

  void deserialize(const std::string& data) override {
    std::istringstream iss(data);
    std::string token;

    std::getline(iss, token, ';');
    feedbackId = std::stoi(token);

    std::getline(iss, token, ';');
    userId = std::stoi(token);

    std::getline(iss, token, ';');
    menuItemId = std::stoi(token);

    std::getline(iss, token, ';');
    rating = std::stoi(token);

    std::getline(iss, token, ';');
    comment = token;

    std::getline(iss, token, ';');
    date = token;
  }
};
