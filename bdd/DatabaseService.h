#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H
#include <iostream>
#include "Database.h"
#include "../Entities/User.h"

class DatabaseService {
    private:
        static std::shared_ptr<sql::Connection> conn;

    public:
        static void setConn(std::shared_ptr<sql::Connection>);
        static User getUserById(int id);
        static bool insertUser(User);
};

#endif