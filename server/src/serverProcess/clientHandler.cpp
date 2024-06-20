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
  while(running){
     
    std::vector<std::string> dataRecieved = receiveRequest();
    if (dataRecieved.size() == 0) {
      continue; // Continue to listen for further data
    }
    std::cout<<"Data recieved operation: "<<dataRecieved[0]<<std::endl;
    std::cout<<"Data recieved userId: "<<dataRecieved[1]<<std::endl;
    std::cout<<"Data recieved password: "<<dataRecieved[2]<<std::endl;
    std::vector<std::string> response = requestProcessor.processRequest(dataRecieved);

    if (!sendRequest(response)) {
      std::cerr << "Failed to send response" << std::endl;
      break;
    }
       
  }

  // Closing the socket
  close(clientSocket);
}

bool ClientHandler::sendRequest(std::vector<std::string> request) {
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
  return valsend > 0;
}

std::vector<std::string> ClientHandler::receiveRequest() {
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
  if(data.size() > 0){
  std::cout << "number of bytes read ds : " << data.size() << "\n";

  std::vector<std::string> valueData = vectorSerializer.deserialize(std::string(data.begin(), data.end()));
    return valueData;
  }
  return std::vector<std::string>();
  
}
