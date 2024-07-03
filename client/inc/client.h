#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <netinet/in.h>
#include "socketException.h"

class Client {
public:
    explicit Client(int server_port);
    ~Client();
    void connectToServer();
    void disconnect();
    int getSocket() const;
    struct sockaddr_in getAddress() const;

private:
    int server_port;
    int clientSocket;
    struct sockaddr_in serv_addr;
    void createSocket();
    void setupAddress();
    void handleError(const std::string& errorMessage) const;
};

#endif // CLIENT_H
