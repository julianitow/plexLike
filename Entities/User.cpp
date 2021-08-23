#include "User.h"

User::User(const char* username, const char* password) {
    this->username = username;
    this->password = password;
    this->logged = false;
}

const char* User::_username() {
    return this->username;
}

const char* User::_password() {
    return this->password;
}

void User::setLogged(bool logged){
    this->logged = logged;
}

bool User::isLoggedIn(){
    return this->logged;
}