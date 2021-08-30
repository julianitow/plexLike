#ifndef USER_H
#define USER_H

#include <iostream>

class User {
    private:
        std::string username;
        std::string password;
        bool logged;
    
    public:
        User(std::string, std::string);
        std::string _username();
        std::string _password();
        void setLogged(bool);
        bool isLoggedIn();
};
#endif