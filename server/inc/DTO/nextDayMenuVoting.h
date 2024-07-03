#pragma once

#include "serializable.h"
#include <sstream>
#include <string>

struct NextDayMenuVoting : public Serializable {
  int menuItemId;
  int voteCount;
  double rating;
  std::string sentiments;

  NextDayMenuVoting(int menuItemId = 0, int voteCount = 0, double rating = 0.0, std::string sentiments = "")
      : menuItemId(menuItemId), voteCount(voteCount), rating(rating), sentiments(sentiments) {}

  std::string serialize() const override {
    return std::to_string(menuItemId) + ";" +
           std::to_string(voteCount) + ";" +
           std::to_string(rating) + ";" +
           sentiments;
  }

  void deserialize(const std::string& data) override {
    std::istringstream iss(data);
    std::string token;

    std::getline(iss, token, ';');
    menuItemId = std::stoi(token);

    std::getline(iss, token, ';');
    voteCount = std::stoi(token);

    std::getline(iss, token, ';');
    rating = std::stod(token);

    std::getline(iss, sentiments, ';');
  }
};
