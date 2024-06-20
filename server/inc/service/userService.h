#include"../DAO/IUserDAO.h"

class UserService
{
public:
    UserService(IUserDAO* userDAO);
    bool addUser(const User& user);
    bool deleteUserByID(int userId);
    User getUserById(int userId);

    std::vector<User> getAllUsers();
    bool authenticateUser(const int& userId, const std::string& password);

    ~UserService() = default;
private:    
    IUserDAO* userDAO;
};
