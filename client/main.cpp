#include <iostream>
#include <csignal>
#include "./inc/client.h"
#include "./inc/userInterface.h"

Client * clientInstance = nullptr;
void clientHandlerWrapper(int signal) {
    clientInstance->disconnect();  
    exit(signal);
}


int main() {
    int server_port = 8082;

    Client client(server_port);
    UserInterface ui(client);
    ui.run();
    clientInstance = &client;
    std::signal(SIGINT, clientHandlerWrapper);

    return 0;
}
