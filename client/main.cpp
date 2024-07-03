#include <iostream>
#include <csignal>
#include "./inc/client.h"
#include "./inc/userInterfaceController.h"

Client * clientInstance = nullptr;

void clientHandlerWrapper(int signal) {
    if (clientInstance) {
        clientInstance->disconnect();
    }
    exit(signal);
}

int main() {
    int server_port = 8082;

    try {
        Client client(server_port);
        clientInstance = &client;
        std::signal(SIGINT, clientHandlerWrapper);

        UserInterfaceController* userInterfaceController = new UserInterfaceController(client);
        userInterfaceController->run();

        delete userInterfaceController;
    }
    catch (const SocketException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}