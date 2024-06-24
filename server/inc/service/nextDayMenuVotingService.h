#ifndef RECOMMENDATION_SELECTION_SERVICE_H
#define RECOMMENDATION_SELECTION_SERVICE_H

#include"../DAO/INextDayMenuVotingDAO.h"
#include"../DTO/menuItem.h"
#include <vector>

class NextDayMenuVotingService
{
public:
    NextDayMenuVotingService(INextDayMenuVotingDAO* NextDayMenuVotingDAO);
    bool addNextDayMenuRollout(const std::vector<NextDayMenuVoting>& nextDayMenu);
    std::vector<NextDayMenuVoting> getAllNextDayMenuRollOutItem();
    bool increaseVoteCountForMenuItemId(const int& menuItemId);
    bool deleteMenuRolledOut();
    ~NextDayMenuVotingService() = default;
private:
    INextDayMenuVotingDAO* NextDayMenuVotingDAO;
};
#endif