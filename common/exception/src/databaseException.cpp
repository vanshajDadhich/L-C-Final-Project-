#include "../inc/databaseException.h"

// DatabaseException
DatabaseException::DatabaseException(const std::string& message)
    : message_(message) {}

const char* DatabaseException::what() const noexcept {
    return message_.c_str();
}

// ConnectionException
ConnectException::ConnectException(const std::string& message)
    : DatabaseException(message) {}

// InitializationException
InitializationException::InitializationException(const std::string& message)
    : DatabaseException(message) {}

// QueryException
QueryException::QueryException(const std::string& message)
    : DatabaseException(message) {}
