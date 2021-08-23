#include "User.h"

User::User(const char* username, const char* password) {
    this->username = username;
    this->password = password;
}

const char* User::_username() {
    return this->username;
}

const char* User::_password() {
    return this->password;
}