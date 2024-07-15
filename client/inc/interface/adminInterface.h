#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include "IUserInterface.h"

class AdminInterface : public IUserInterface {
public:
    AdminInterface(RequestHandler* requestHandler);

    void showMenu() override;

private:
    RequestHandler* requestHandler;

    void showAddItemPrompt();
    void showDeleteItemPrompt();
    void showMenuItemList();
    void addUserPrompt();
    void showUpdateMenuItemPrompt();
    void displayMenuItemDetails(const MenuItem& menuItem);
    MenuItem updateMenuItemFromUserInput(MenuItem menuItem);
};

#endif
