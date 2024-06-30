#ifndef NextDayMenuVotingDAO_H
#define NextDayMenuVotingDAO_H

#include "INextDayMenuVotingDAO.h"
#include "databaseConnection.h"
#include"../DTO/menuItem.h"
#include<vector>

class NextDayMenuVotingDAO : public INextDayMenuVotingDAO {
public:
    NextDayMenuVotingDAO();

    bool addNextDayMenuRollout(const std::vector<NextDayMenuVoting>& nextDayMenu) override;
    std::vector<NextDayMenuVoting> getAllNextDayMenuRollOutItem() override;
    bool increaseVoteCountForMenuItemId(const int& menuItemId) override;
    bool deleteMenuRolledOut() override;
    int getMostVotedMenuItemIdForMenuType(MenuItemType menuItemType) override;

private:
    std::shared_ptr<DatabaseConnection> databaseConnection;
};

#endif