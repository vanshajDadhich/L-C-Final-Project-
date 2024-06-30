#include "../../inc/service/nextDayMenuVotingService.h"


NextDayMenuVotingService::NextDayMenuVotingService(INextDayMenuVotingDAO* recommandationSelectionDAO)
    : nextDayMenuVotingDAO(recommandationSelectionDAO) {}

bool NextDayMenuVotingService::addNextDayMenuRollout(const std::vector<NextDayMenuVoting>& nextDayMenu) {
    return nextDayMenuVotingDAO->addNextDayMenuRollout(nextDayMenu);
}

std::vector<NextDayMenuVoting> NextDayMenuVotingService::getAllNextDayMenuRollOutItem() {
    return nextDayMenuVotingDAO->getAllNextDayMenuRollOutItem();
}

bool NextDayMenuVotingService::increaseVoteCountForMenuItemId(const int& menuItemId) {
    return nextDayMenuVotingDAO->increaseVoteCountForMenuItemId(menuItemId);
}

bool NextDayMenuVotingService::deleteMenuRolledOut(){
    return nextDayMenuVotingDAO->deleteMenuRolledOut();
}

std::vector<int> NextDayMenuVotingService::getMostVotedMenuItemIds(){
    std::vector<int> mostVotedMenuItemIds;
    mostVotedMenuItemIds.push_back(nextDayMenuVotingDAO->getMostVotedMenuItemIdForMenuType(MenuItemType::Breakfast));
    mostVotedMenuItemIds.push_back(nextDayMenuVotingDAO->getMostVotedMenuItemIdForMenuType(MenuItemType::Lunch));
    mostVotedMenuItemIds.push_back(nextDayMenuVotingDAO->getMostVotedMenuItemIdForMenuType(MenuItemType::Dinner));

    return mostVotedMenuItemIds;
}