#ifndef INextDayMenuVotingDAO_H
#define INextDayMenuVotingDAO_H

#include "../DTO/nextDayMenuVoting.h"
#include <vector>

class INextDayMenuVotingDAO {
public:

    virtual bool addNextDayMenuRollout(const std::vector<NextDayMenuVoting>& nextDayMenu) = 0;
    virtual std::vector<NextDayMenuVoting> getAllNextDayMenuRollOutItem() = 0;
    virtual bool increaseVoteCountForMenuItemId(const int& menuItemId) = 0;
    virtual bool deleteMenuRolledOut() = 0;
};

#endif // INextDayMenuVotingDAO_H