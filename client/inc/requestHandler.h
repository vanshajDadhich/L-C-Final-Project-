#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <string>
#include <vector>
#include <netinet/in.h>
#include "vectorSerializer.h"

class RequestHandler {
public:
    RequestHandler(int clientSocket, struct sockaddr_in serv_addr);
    void sendRequest(std::string request);
    std::string receiveResponse();
private:
    int clientSocket;
    struct sockaddr_in serv_addr;
    VectorSerializer vectorSerializer;
};

#endif // REQUESTHANDLER_H
