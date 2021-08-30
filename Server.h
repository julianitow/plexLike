#ifndef SERVER_H
#define SERVER_H

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

#include "bdd/Database.h"
#include "bdd/DatabaseService.h"
#include "Entities/User.h"

#include "Media/MediaManager/MediaManager.h"

#include "FilesServices.h"

class Server {
    private:
        std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
        Pistache::Rest::Router router;

        Database* db;
        static Server* instance;

        std::map<int, User*> usersConnected;

        MediaManager mediaManager;

        explicit Server(Pistache::Address);

        void setupRoutes();
        void listDirRoute(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
        User loginUser();
        User createUser(const char*, const char*);
        
        void testRoute(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
        void testAgainRoute(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
        void signupRoute(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
        void loginRoute(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
    
    public:
        static Server* getInstance(Pistache::Address);
        void init(size_t = 2);
        void start();
        static void shutdown(int);
        static void execInThread(Server*, int = 2);

        void runMediaManager();
};

#endif