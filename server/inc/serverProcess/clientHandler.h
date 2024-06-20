
#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <string>
#include <vector>
#include "requestProcessor.h"
#include "vectorSerializer.h"

class ClientHandler {
public:
    ClientHandler(int clientSocket);
    void handle();

private:
    int clientSocket;
    bool running;
    RequestProcessor requestProcessor;
    VectorSerializer vectorSerializer;
    
    bool sendRequest(std::vector<std::string> request);
    std::vector<unsigned char> processRequest( std::vector<unsigned char> requestBuffer);
    std::vector<std::string> receiveRequest();
};

#endif // CLIENTHANDLER_H
