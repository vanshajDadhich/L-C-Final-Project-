#ifndef RECOMMENDATION_SELECTION_SERVICE_H
#define RECOMMENDATION_SELECTION_SERVICE_H

#include"../DAO/IRecommendationSelectionDAO.h"
#include"../DTO/menuItem.h"
#include <vector>

class RecommendationSelectionService
{
public:
    RecommendationSelectionService(IRecommendationSelectionDAO* recommendationSelectionDAO);
    bool addRecommendationSelection(const RecommendationSelection& recommendationSelection);
    RecommendationSelection getRecommendationSelectionById(int recommendationSelectionId);
    std::vector<RecommendationSelection> getAllRecommendationSelectionsForMenuType(MenuItemType menuItemType);
    ~RecommendationSelectionService() = default;
private:
    IRecommendationSelectionDAO* recommendationSelectionDAO;
};
#endif