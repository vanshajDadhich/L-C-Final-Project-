
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
    
    bool sendRequest(std::string request);
    std::string receiveRequest();
};

#endif // CLIENTHANDLER_H
