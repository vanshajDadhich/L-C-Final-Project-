#include "../../inc/communication/server.h"

Server::Server(int port) : port(port), server_fd(-1), running(false) {
    memset(&address, 0, sizeof(address));
}

Server::~Server() {
    stop();
}

void Server::start() {
    try {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1) {
            throw ConnectionException("Failed to create socket");
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
            throw ConnectionException("Failed to bind socket");
        }

        if (listen(server_fd, 3) == -1) {
            throw ConnectionException("Failed to listen on socket");
        }

        running.store(true);
        std::thread acceptThread(&Server::acceptClients, this);
        acceptThread.detach();

        std::cout << "Server started on port " << port << std::endl;
    } catch (const ConnectionException& e) {
        std::cerr << "Connection exception: " << e.what() << std::endl;
        stop();
        throw;
    }
}

void Server::stop() {
    running.store(false);
    if (server_fd != -1) {
        close(server_fd);
    }

    std::lock_guard<std::mutex> lock(clientsMutex);
    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }

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
                std::cerr << "Accept failed: " << strerror(errno) << std::endl;
            }
            continue;
        }

        std::lock_guard<std::mutex> lock(clientsMutex);
        clientSockets.push_back(clientSocket);
        clientThreads.emplace_back(&ClientHandler::handle, ClientHandler(clientSocket));
    }
}
