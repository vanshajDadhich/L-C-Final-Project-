#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <vector>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include "requestProcessor.h"
#include "socketException.h"

class ClientHandler {
public:
    explicit ClientHandler(int clientSocket);
    void handle();

private:
    int clientSocket;
    bool running;
    RequestProcessor requestProcessor;

    bool sendRequest(const std::string& request);
    std::string receiveRequest();
};

#endif
