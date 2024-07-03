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

public:
    AdminInterface(RequestHandler* requestHandler);

    void showMenu() override;
};

#endif
