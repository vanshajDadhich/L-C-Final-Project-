#ifndef USERINTERFACECONTROLLER_H
#define USERINTERFACECONTROLLER_H

#include "communication/client.h"
#include "interface/adminInterface.h"
#include "interface/chefInterface.h"
#include "interface/employeeInterface.h"

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
    void initializeUserInterface(Role userRole);
    void loginPrompt();
};

#endif