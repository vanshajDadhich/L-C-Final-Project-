#ifndef RECOMMENDATIONSELECTIONDAO_H
#define RECOMMENDATIONSELECTIONDAO_H

#include "IRecommendationSelectionDAO.h"
#include "databaseConnection.h"
#include"../DTO/menuItem.h"
#include<vector>

class RecommendationSelectionDAO : public IRecommendationSelectionDAO {
public:
    RecommendationSelectionDAO();

    // Member function declarations for entries in recommendationselection.h
    bool addRecommendationSelection(const RecommendationSelection& selection);
    RecommendationSelection getRecommendationSelectionById(const int& id);
    bool deleteRecommendationSelection(const int& id);
    RecommendationSelection getRecommendationSelectionByMenuItemId(const int& menuItemId);
    std::vector<RecommendationSelection> getAllRecommendationSelectionsForMenuType(MenuItemType menuItemType);

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};

#endif