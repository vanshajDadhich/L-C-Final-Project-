#include "../inc/socketException.h"

SocketException::SocketException(const std::string& message) 
    : message(message) {
    std::cerr << "SocketException: " << message << std::endl;
}

const char* SocketException::what() const noexcept {
    return message.c_str();
}

ConnectionException::ConnectionException(const std::string& message) 
    : SocketException(message) {}

DisconnectionException::DisconnectionException(const std::string& message) 
    : SocketException(message) {}

RequestException::RequestException(const std::string& message) 
    : SocketException(message) {}

ResponseException::ResponseException(const std::string& message) 
    : SocketException(message) {}
