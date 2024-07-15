#ifndef CHEFINTERFACE_H
#define CHEFINTERFACE_H

#include "IUserInterface.h"

class ChefInterface : public IUserInterface {
public:
    ChefInterface(RequestHandler* requestHandler);

    void showMenu() override;

private:
    RequestHandler* requestHandler;

    void showRecommendedMenuAndRolloutForTomorrow();
    void rollOutMenuForTomorrow(std::vector<std::pair<MenuItemType, int>> recommendedMenuItem);
    void showMenuItemList();
    void publishMenuForToday();
    void showDiscardMenuList();
    void showNextDayMenuVoting();
    void showDiscardMenuItemActionPrompt(const std::vector<int>& discardMenuItemIdList);
    void removeMenuItemFromList(const std::vector<int>& discardMenuItemIdList);
    void getMenuItemIdForDetailedFeedback(const std::vector<int>& discardMenuItemIdList);
    std::vector<std::pair<MenuItemType, int>> showRecommendedMenu(MenuItemType menuItemType);
    std::string getValidMenuItemIdsForMealType(const std::vector<std::pair<MenuItemType, int>>& recommendedMenuItem, MenuItemType menuItemType);
    std::string validateMenuItemsAgainstRecommendedItems(const std::vector<std::pair<MenuItemType, int>>& recommendedMenuItem,
                            const std::string& menuItemString,
                            MenuItemType menuItemType);
};

#endif
