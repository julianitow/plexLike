#include "User.h"

User::User(std::string username, std::string password) {
    this->username = username;
    this->password = password;
    this->logged = false;
}

std::string User::_username() {
    return this->username;
}

std::string User::_password() {
    return this->password;
}

void User::setLogged(bool logged){
    this->logged = logged;
}

bool User::isLoggedIn(){
    return this->logged;
}