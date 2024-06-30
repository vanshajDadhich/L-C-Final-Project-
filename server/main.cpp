#include <iostream>
#include <csignal>
#include <thread>
#include "./inc/serverProcess/server.h"

Server* serverInstance = nullptr;

void signalHandlerWrapper(int signal) {
    if (serverInstance) {
        std::cout << "Signal " << signal << " received. Shutting down the server..." << std::endl;
        serverInstance->stop();
        std::cout << "Server stopped." << std::endl;
    }
    exit(signal);
}

int main() {
    Server server(8082);
    serverInstance = &server;
    server.start();

    std::cout << "Server started on port 8082. Press Ctrl+C to stop the server." << std::endl;

    std::signal(SIGINT, signalHandlerWrapper);

    // Main loop (example: sleeping for 1 second)
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
