#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "client.h"
#include "requestHandler.h"

class UserInterface {
public:
    UserInterface(Client& client);
    void run();

private:
    Client& client;
    RequestHandler* requestHandler;

    void handleUserInput();
    void showMenuPrompt(std::string userRole);
    int showAdminMenu();
    void showAddItemPrompt();
    void showUpdateMenuPrompt();
    void showDeleteItemPrompt();
    void showMenu();
    void addUserPrompt();

    void loginPrompt();
    std::vector<std::string> getDataToUpdate();

};

#endif // USERINTERFACE_H
