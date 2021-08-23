#ifndef DATABASE_H
#define DATABASE_H
#include <mariadb/conncpp.hpp>

class Database {
    private:
        static const char* host;
        static const char* user;
        static const char* password;
        static const char* db;
        static int port;
        sql::Driver* driver;
        static std::shared_ptr<sql::Connection> conn;
        explicit Database();
    public:
        static std::shared_ptr<sql::Connection> getInstance();
        static void setPort(int = 3306);
        static void setHost(const char*);
        static void setUser(const char*);
        static void setPassword(const char*);
        static void setDb(const char*);
};

#endif