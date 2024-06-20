#include "../../inc/serverProcess/server.h"
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

Server::Server(int port) : port(port), server_fd(-1), running(false) {
    memset(&address, 0, sizeof(address));
}

Server::~Server() {
    stop();
}

void Server::start() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(server_fd);
        return;
    }

    if (listen(server_fd, 3) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(server_fd);
        return;
    }

    running.store(true);
    std::thread acceptThread(&Server::acceptClients, this);
    acceptThread.detach();

    std::cout << "Server started on port " << port << std::endl;
}

void Server::stop() {
    running.store(false);
    close(server_fd);

    std::lock_guard<std::mutex> lock(clientsMutex);
    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }

    // for (auto& thread : clientThreads) {
    //     if (thread.joinable()) {
    //         thread.join();
    //     }
    // }

    clientSockets.clear();
    clientThreads.clear();

    std::cout << "Server stopped" << std::endl;
}

void Server::acceptClients() {
    while (running) {
        int clientSocket;
        int addrlen = sizeof(address);
        clientSocket = accept(server_fd, (struct sockaddr*)&address, (socklen_t *)&addrlen);

        if (clientSocket < 0) {
            if (running) {
                perror("Accept failed");
                close(server_fd);
            }
            continue;
        }

        std::lock_guard<std::mutex> lock(clientsMutex);
        clientSockets.push_back(clientSocket);
        clientThreads.push_back(std::thread(&ClientHandler::handle, ClientHandler(clientSocket)));
    }
}