#ifndef USERINTERFACECONTROLLER_H
#define USERINTERFACECONTROLLER_H

#include "client.h"
#include "IUserInterface.h"
#include "adminInterface.h"
#include "chefInterface.h"
#include "employeeInterface.h"

class UserInterfaceController {
public:
    UserInterfaceController(Client& client);
    void run();

private:
    Client& client;
    RequestHandler* requestHandler;
    int userIdLoggedIn;
    IUserInterface* userInterface;

    void handleUserInput();
    void showMenuPrompt(std::string userRole);
    void initializeUserInterface(Role userRole);
    void loginPrompt();
};

#endif 