#include "../../inc/serverProcess/clientHandler.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "../../inc/serverProcess/requestProcessor.h"

#define BUFFER_SIZE 4096

ClientHandler::ClientHandler(int clientSocket)
    : clientSocket(clientSocket), running(true) {}

void ClientHandler::handle() {
    while (running) {
        std::vector<std::string> dataReceived = receiveRequest();
        if (dataReceived.empty()) {
            continue; // Continue to listen for further data
        }
        
        std::vector<std::string> response = requestProcessor.processRequest(dataReceived);

        if (!sendRequest(response)) {
            std::cerr << "Failed to send response" << std::endl;
            break;
        }
    }

    // Closing the socket
    close(clientSocket);
}

bool ClientHandler::sendRequest(std::vector<std::string> response) {
    std::vector<unsigned char> responseBuffer;
    auto serializedResponse = vectorSerializer.serialize(response);
    responseBuffer.insert(responseBuffer.end(), serializedResponse.begin(), serializedResponse.end());

    int valsend = send(clientSocket, responseBuffer.data(), responseBuffer.size(), 0);
    if (valsend < 0) {
        std::cerr << "Send failed with error code: " << valsend << "\n";
        return false;
    }
    std::cout << "Number of bytes sent: " << valsend << "\n";
    return true;
}

std::vector<std::string> ClientHandler::receiveRequest() {
    char buffer[BUFFER_SIZE] = {0};

    int valread = read(clientSocket, buffer, BUFFER_SIZE);
    if (valread < 0) {
        std::cerr << "Read failed with error code: " << valread << "\n";
        return std::vector<std::string>();
    }

    std::cout << "Number of bytes read: " << valread << "\n";

    std::vector<unsigned char> data(buffer, buffer + valread);
    std::vector<std::string> request = vectorSerializer.deserialize(std::string(data.begin(), data.end()));
    return request;
}
