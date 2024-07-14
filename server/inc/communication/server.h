#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include <mutex>
#include <atomic>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "clientHandler.h"

class Server {
public:
    explicit Server(int port);
    ~Server();
    void start();
    void stop();

private:
    int port;
    int server_fd;
    struct sockaddr_in address;
    std::vector<int> clientSockets;
    std::vector<std::thread> clientThreads;
    std::mutex clientsMutex;
    std::atomic<bool> running;

    void acceptClients();
};

#endif
