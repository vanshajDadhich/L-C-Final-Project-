#ifndef DATABASE_EXCEPTION_H
#define DATABASE_EXCEPTION_H

#include <exception>
#include <string>
#include <iostream>

class DatabaseException : public std::exception {
public:
    explicit DatabaseException(const std::string& message);
    const char* what() const noexcept override;

protected:
    std::string message_;
};

class ConnectException : public DatabaseException {
public:
    explicit ConnectException(const std::string& message);
};

class InitializationException : public DatabaseException {
public:
    explicit InitializationException(const std::string& message);
};

class QueryException : public DatabaseException {
public:
    explicit QueryException(const std::string& message);
};

#endif
