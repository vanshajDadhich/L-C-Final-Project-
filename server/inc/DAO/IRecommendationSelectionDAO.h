#ifndef IRECOMMENDATIONSELECTIONDAO_H
#define IRECOMMENDATIONSELECTIONDAO_H

#include "../DTO/recommendationSelection.h"
#include <vector>

class IRecommendationSelectionDAO {
public:

    virtual bool addRecommendationSelection(const RecommendationSelection& selection) = 0;

    virtual RecommendationSelection getRecommendationSelectionById(const int& id) = 0;

    virtual bool deleteRecommendationSelection(const int& id) = 0;

    virtual RecommendationSelection getRecommendationSelectionByMenuItemId(const int&  menuItemId) = 0;

    virtual std::vector<RecommendationSelection> getAllRecommendationSelectionsForMenuType(MenuItemType menuItemType) = 0;
};

#endif // IRECOMMENDATIONSELECTIONDAO_H
