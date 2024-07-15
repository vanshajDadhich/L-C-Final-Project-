#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <exception>
#include <string>
#include<iostream>

class SocketException : public std::exception {
public:
    explicit SocketException(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string message;
};

class ConnectionException : public SocketException {
public:
    explicit ConnectionException(const std::string& message);
};

class DisconnectionException : public SocketException {
public:
    explicit DisconnectionException(const std::string& message);
};

class RequestException : public SocketException {
public:
    explicit RequestException(const std::string& message);
};

class ResponseException : public SocketException {
public:
    explicit ResponseException(const std::string& message);
};

#endif
