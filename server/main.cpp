#include <iostream>
#include <csignal>
#include <thread>
#include "./inc/communication/server.h"

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
    try {
        Server server(8082);
        serverInstance = &server;
        server.start();

        std::cout << "Server started on port 8081. Press Ctrl+C to stop the server." << std::endl;
        std::signal(SIGINT, signalHandlerWrapper);

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const SocketException& e) {
        std::cerr << "Socket exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
