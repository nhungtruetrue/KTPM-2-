#pragma once
class User {
public:
    std::string username;
    std::string password;
    bool isAdmin;

    User(const std::string& _username, const std::string& _password, bool _isAdmin)
        : username(_username), password(_password), isAdmin(_isAdmin) {}
};
#pragma once
class UserManager {
public:
    std::vector<User> users;

    void addUser(const User& user) {
        users.push_back(user);
    }

    User* findUser(const std::string& username) {
        for (auto& user : users) {
            if (user.username == username) {
                return &user;
            }
        }
        return nullptr;
    }

    bool authenticateUser(const std::string& username, const std::string& password) {
        User* user = findUser(username);
        return (user != nullptr && user->password == password);
    }

    bool isAdmin(const std::string& username) {
        User* user = findUser(username);
        return (user != nullptr && user->isAdmin);
    }
};
