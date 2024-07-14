#include "../../inc/DAO/databaseConnection.h"
#include <cppconn/connection.h>
#include <mysql_driver.h>
#include <stdexcept>

std::shared_ptr<sql::Connection> DatabaseConnection::connection = nullptr;
std::shared_ptr<DatabaseConnection> DatabaseConnection::instance = nullptr;

std::shared_ptr<sql::Connection> DatabaseConnection::getConnection() {
  if (connection != nullptr) {
    return connection;
  }
  throw InitializationException("Connection is not initialized. Need to call InitDbConnection first");
}

void DatabaseConnection::initDbConnection(const std::string& hostName,
                                          const std::string& userName,
                                          const std::string& password,
                                          const std::string& schemaName) {
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
    connection = std::shared_ptr<sql::Connection>(driver->connect(hostName, userName, password));
    if (connection != nullptr) {
      connection->setSchema(schemaName);
    } else {
      throw ConnectException("Failed to establish connection.");
    }
}

DatabaseConnection::DatabaseConnection() {}

std::shared_ptr<DatabaseConnection> DatabaseConnection::getInstance() {
  if (instance == nullptr) {
    instance = std::shared_ptr<DatabaseConnection>(new DatabaseConnection());
  }
  return instance;
}

DatabaseConnection::~DatabaseConnection() {
  if (connection != nullptr) {
    connection->close();
  }
}
