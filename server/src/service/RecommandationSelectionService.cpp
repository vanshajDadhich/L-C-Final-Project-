#include "../../inc/service/recommandationSelectionService.h"


RecommendationSelectionService::RecommendationSelectionService(IRecommendationSelectionDAO* recommandationSelectionDAO)
    : recommendationSelectionDAO(recommandationSelectionDAO) {}

bool RecommendationSelectionService::addRecommendationSelection(const RecommendationSelection& recommandationSelection) {
    return recommendationSelectionDAO->addRecommendationSelection(recommandationSelection);
}

RecommendationSelection RecommendationSelectionService::getRecommendationSelectionById(int recommendationSelectionId) {
    return recommendationSelectionDAO->getRecommendationSelectionById(recommendationSelectionId);
}

std::vector<RecommendationSelection> RecommendationSelectionService::getAllRecommendationSelectionsForMenuType(MenuItemType menuItemType) {
    return recommendationSelectionDAO->getAllRecommendationSelectionsForMenuType(menuItemType);
}