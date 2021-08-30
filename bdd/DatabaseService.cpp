#include "DatabaseService.h"

std::shared_ptr<sql::Connection> DatabaseService::conn;

void DatabaseService::setConn(std::shared_ptr<sql::Connection> conn) {
    DatabaseService::conn = conn;
}

bool DatabaseService::insertUser(User user) {
    try {
        std::unique_ptr<sql::PreparedStatement> stmnt(DatabaseService::conn->prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)"));
        stmnt->setString(1, user._username());
        stmnt->setString(2, user._password());
        sql::ResultSet* res = stmnt->executeQuery();
        return true;
    } catch (sql::SQLException  &err) {
        std::cerr << err.what() << std::endl;
        return false;
    }
}

User DatabaseService::getUser(User user) {
    try {
        std::unique_ptr<sql::PreparedStatement> stmnt(DatabaseService::conn->prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?"));
        stmnt->setString(1, user._username());
        stmnt->setString(2, user._password());
        sql::ResultSet* res = stmnt->executeQuery();
        std::string username;
        std::string password;
        while(res->next()) {
            username = res->getString("username");
            password = res->getString("password");
            std::cout << username << std::endl;
            std::cout << password << std::endl;
        }
        User user(username.c_str(), password.c_str());
        return user;
        
    } catch (sql::SQLException  &err) {
        std::cerr << err.what() << std::endl;
    }
}