#pragma once

#include "serializable.h"
#include "menuItem.h"
#include <sstream>
#include <string>

struct RecommendationSelection : public Serializable {
  int SelectionId;
  int menuItemId;
  int selectionCount;
  int sentimentScore;

  RecommendationSelection(int SelectionId = 0, int menuItemId = 0, int selectionCount = 0, int sentimentScore = 0)
      : SelectionId(SelectionId), menuItemId(menuItemId), selectionCount(selectionCount), sentimentScore(sentimentScore) {}

  RecommendationSelection(){}

  std::string serialize() const override {
    return std::to_string(SelectionId) + ";" +
           std::to_string(menuItemId) + ";" +
           std::to_string(selectionCount) + ";" +
           std::to_string(sentimentScore);
  }

  void deserialize(const std::string& data) override {
    std::istringstream iss(data);
    std::string token;

    std::getline(iss, token, ';');
    SelectionId = std::stoi(token);

    std::getline(iss, token, ';');
    menuItemId = std::stoi(token);

    std::getline(iss, token, ';');
    selectionCount = std::stoi(token);

    std::getline(iss, token, ';');
    sentimentScore = std::stoi(token);
  }
};
