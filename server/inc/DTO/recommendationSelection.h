  #pragma once

  #include "menuItem.h"

  #include <cstdint>
  struct RecommendationSelection {
    int SelectionId;
    int menuItemId;
    int selectionCount;
    int sentimentScore;
    RecommendationSelection(int SelectionId, int menuItemId, int selectionCount,
                int sentimentScore)
        : SelectionId(SelectionId), menuItemId(menuItemId), selectionCount(selectionCount),
          sentimentScore(sentimentScore) {}
  };