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
};

#endif // USERINTERFACE_H
