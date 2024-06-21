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


void RequestHandler::sendRequest(std::vector<std::string> request) {
    std::vector<unsigned char> requestBuffer;
    auto serializedRequest = vectorSerializer.serialize(request);
    requestBuffer.insert(requestBuffer.end(), serializedRequest.begin(), serializedRequest.end());

    int valsend = send(clientSocket, requestBuffer.data(), requestBuffer.size(), 0);
    if (valsend < 0) {
        std::cerr << "Send failed with error code: " << valsend << "\n";
    } else {
        std::cout << "Number of bytes sent: " << valsend << "\n";
    }
}

std::vector<std::string> RequestHandler::receiveResponse() {
    char buffer[BUFFER_SIZE] = {0};

    int valread = read(clientSocket, buffer, BUFFER_SIZE);
    if (valread < 0) {
        std::cerr << "Read failed with error code: " << valread << "\n";
        return std::vector<std::string>();
    }

    std::cout << "Number of bytes read: " << valread << "\n";

    std::vector<unsigned char> data(buffer, buffer + valread);
    std::vector<std::string> response = vectorSerializer.deserialize(std::string(data.begin(), data.end()));
    return response;
}
