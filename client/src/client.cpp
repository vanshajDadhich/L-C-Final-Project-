#include "../inc/client.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

Client::Client(const int&  server_port)
    : server_port(server_port), clientSocket(0) {
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(server_port);
}

Client::~Client() {
    disconnect();
}

bool Client::connectToServer() {
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return false;
    }

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return false;
    }

    if (connect(clientSocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return false;
    }

    return true;
}

void Client::disconnect() {
    if (clientSocket != 0) {
        close(clientSocket);
        clientSocket = 0;
    }
}

int Client::getSocket() const {
    return clientSocket;
}

struct sockaddr_in Client::getAddress() const {
    return serv_addr;
}
