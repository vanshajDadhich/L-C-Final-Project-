#include "../inc/requestHandler.h"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <netinet/in.h>

#define BUFFER_SIZE 4096

RequestHandler::RequestHandler(int clientSocket, struct sockaddr_in serv_addr)
    : clientSocket(clientSocket), serv_addr(serv_addr) {}

void RequestHandler::sendRequest(const std::string& request) {
    std::vector<unsigned char> requestBuffer(request.begin(), request.end());

    int bytesSent = send(clientSocket, requestBuffer.data(), requestBuffer.size(), 0);
    if (bytesSent < 0) {
        throw RequestException("Send failed with error code: " + std::to_string(bytesSent));
    }
    std::cout << "Number of bytes sent: " << bytesSent << std::endl;
}

std::string RequestHandler::receiveResponse() {
    char buffer[BUFFER_SIZE] = {0};

    int bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
    if (bytesRead < 0) {
        throw ResponseException("Read failed with error code: " + std::to_string(bytesRead));
    }
    if (bytesRead > 0) {
        std::cout << "Number of bytes read: " << bytesRead << std::endl;
    }

    return std::string(buffer, bytesRead);
}
