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

  int valsend = 0;
  do {
    valsend = send(clientSocket, requestBuffer.data(), requestBuffer.size(), 0);
    if (valsend > 0) {
      requestBuffer.erase(requestBuffer.begin(),
                          requestBuffer.begin() + valsend);
    }
  } while (valsend > 0 && requestBuffer.size() > 0);
  shutdown(clientSocket, SHUT_WR);
  std::cout << "number of bytes sent : " << valsend << "\n";
}

std::vector<std::string> RequestHandler::receiveResponse() {
  char buffer[BUFFER_SIZE] = {0};

  int valread = 0;
  std::vector<unsigned char> data;
  do {
    valread = read(clientSocket, buffer, BUFFER_SIZE);
    if (valread > 0) {
      std::cout << "number of bytes read : " << valread << "\n";
      data.insert(data.end(), buffer, buffer + valread);
    }
  } while (valread > 0);
  std::cout << "number of bytes read ds : " << data.size() << "\n";

  std::vector<std::string> response = vectorSerializer.deserialize(std::string(data.begin(), data.end()));
  return response;
}