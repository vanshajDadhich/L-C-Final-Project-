#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <cppconn/connection.h>
#include <memory>
#include "../../../common/exception/inc/databaseException.h"

class DatabaseConnection {
  static std::shared_ptr<sql::Connection> connection;
  static std::shared_ptr<DatabaseConnection> instance;
  DatabaseConnection();

public:
  DatabaseConnection(const DatabaseConnection &) = delete;
  DatabaseConnection &operator=(const DatabaseConnection &) = delete;
  static void initDbConnection(const std::string &hostName,
                               const std::string &userName,
                               const std::string &password,
                               const std::string &schemaName);
  static std::shared_ptr<DatabaseConnection> getInstance();
  std::shared_ptr<sql::Connection> getConnection();
  ~DatabaseConnection();
  
};

#endif