#pragma once

#include <string>

enum Role : int { Admin = 1, Employee = 2, Chef = 3 };

struct User {
  int userId;
  std::string name;
  std::string password;
  Role role;

  User(int userId, std::string name, int role, std::string password)
      : userId(userId), name(name), password(password),role(static_cast<Role>(role)) {}
};
