#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    std::string username;
    std::string password;
    std::string role; // "admin" or "user"

    static std::vector<User> users; // List of all users
    static const std::string userFile; // File to save/load user data

public:
    static std::string currentUser;
    User() = default;
    User(const std::string& uname, const std::string& pass, const std::string& r);

    static bool registerUser(const std::string& uname, const std::string& pass, const std::string& r);
    static bool loginUser(const std::string& uname, const std::string& pass);
    static bool isAdmin(const std::string& uname);

    static void saveUsersToFile();
    static void loadUsersFromFile(const std::string& fileName);
};

#endif
