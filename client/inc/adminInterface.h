#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include "IUserInterface.h"

class AdminInterface : public IUserInterface {
private:
    RequestHandler* requestHandler;

    void showAddItemPrompt();
    void showDeleteItemPrompt();
    void showMenuItemList();
    void addUserPrompt();
    std::string getMenuType(MenuItemType menuItemType);
    std::string getVegetarianPreference(VegetarianPreference vegetarianPreference);
    // std::string getSpicelevelOption

public:
    AdminInterface(RequestHandler* requestHandler);

    void showMenu() override;
};

#endif
