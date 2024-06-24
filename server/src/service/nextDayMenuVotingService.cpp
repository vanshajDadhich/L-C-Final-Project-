#include "../../inc/service/nextDayMenuVotingService.h"


NextDayMenuVotingService::NextDayMenuVotingService(INextDayMenuVotingDAO* recommandationSelectionDAO)
    : NextDayMenuVotingDAO(recommandationSelectionDAO) {}

bool NextDayMenuVotingService::addNextDayMenuRollout(const std::vector<NextDayMenuVoting>& nextDayMenu) {
    return NextDayMenuVotingDAO->addNextDayMenuRollout(nextDayMenu);
}

std::vector<NextDayMenuVoting> NextDayMenuVotingService::getAllNextDayMenuRollOutItem() {
    return NextDayMenuVotingDAO->getAllNextDayMenuRollOutItem();
}

bool NextDayMenuVotingService::increaseVoteCountForMenuItemId(const int& menuItemId) {
    return NextDayMenuVotingDAO->increaseVoteCountForMenuItemId(menuItemId);
}

bool NextDayMenuVotingService::deleteMenuRolledOut(){
    return NextDayMenuVotingDAO->deleteMenuRolledOut();
}