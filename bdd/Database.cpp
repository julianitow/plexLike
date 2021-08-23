#include "Database.h"

int Database::port;
const char* Database::host;
const char* Database::user;
const char* Database::password;
const char* Database::db;
std::shared_ptr<sql::Connection> Database::conn;

Database::Database() {
    this->driver = sql::mariadb::get_driver_instance();
    std::string urlStr = "jdbc:mariadb://" + std::string(Database::host) + ":" + std::to_string(Database::port) + "/" + Database::db;
    sql::SQLString url(urlStr);
    sql::Properties properties({{ "user", Database::user }, { "password", Database::password }});
    Database::conn = std::shared_ptr<sql::Connection>(this->driver->connect(url, properties));
}

std::shared_ptr<sql::Connection> Database::getInstance() {
    if(Database::conn == nullptr) {
        Database* db = new Database();
    }
    return Database::conn;
}



void Database::setPort(int port) {
    Database::port = port;
}

void Database::setHost(const char* host) {
    Database::host = host;
}

void Database::setUser(const char* user) {
    Database::user = user;
}

void Database::setPassword(const char* password) {
    Database::password = password;
}

void Database::setDb(const char* db) {
    Database::db = db;
}