#ifndef RECOMMENDATION_SELECTION_SERVICE_H
#define RECOMMENDATION_SELECTION_SERVICE_H

#include"../DAO/INextDayMenuVotingDAO.h"
#include"../DTO/menuItem.h"
#include <vector>
#include<memory>

class NextDayMenuVotingService
{
public:
    NextDayMenuVotingService(std::unique_ptr<INextDayMenuVotingDAO> nextDayMenuVotingDAO);
    bool addNextDayMenuRollout(const std::vector<NextDayMenuVoting>& nextDayMenu);
    std::vector<NextDayMenuVoting> getAllNextDayMenuRollOutItem();
    bool increaseVoteCountForMenuItemId(const int& menuItemId);
    bool deleteMenuRolledOut();
    std::vector<int> getMostVotedMenuItemIds();
    ~NextDayMenuVotingService() = default;
private:
    std::unique_ptr<INextDayMenuVotingDAO> nextDayMenuVotingDAO;
};
#endif