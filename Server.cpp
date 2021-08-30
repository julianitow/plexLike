#include "Server.h"

Server* Server::instance;

Server::Server(Pistache::Address addr) {
    this->httpEndpoint = std::make_shared<Pistache::Http::Endpoint>(addr);
    this->usersConnected = std::map<int, User*>();

    Database::setDb("plexLike");
    Database::setHost("localhost");
    Database::setUser("plexLike");
    Database::setPassword("plexLike");

    DatabaseService::setConn(Database::getInstance());
}

Server* Server::getInstance(Pistache::Address addr) {
    if(Server::instance == nullptr) {
        Server::instance = new Server(addr);
    }
    return Server::instance;
}

void Server::init(size_t thr) {
    auto opts = Pistache::Http::Endpoint::options()
                    .threads(static_cast<int>(thr))
                    .flags(Pistache::Tcp::Options::ReuseAddr);
    this->httpEndpoint->init(opts);
    this->setupRoutes();
}

void Server::start() {
    this->httpEndpoint->setHandler(this->router.handler());
    this->httpEndpoint->serve();
}

void Server::setupRoutes() {
    using namespace Pistache::Rest;
    Routes::Get(this->router, "/test", Routes::bind(&Server::testRoute, this));
    Routes::Get(this->router, "/testAgain/:param", Routes::bind(&Server::testAgainRoute, this));
    Routes::Get(this->router, "/content", Routes::bind(&Server::listDirRoute, this));
    Routes::Get(this->router, "/signup/:username/:password", Routes::bind(&Server::signupRoute, this));
    Routes::Get(this->router, "/signin/:username/:password", Routes::bind(&Server::loginRoute, this));
}

void Server::testRoute(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    
    response.send(Pistache::Http::Code::Ok, "Access testRoute Success");
}

//TODO: HASH PASSWORD && LOGIN

void Server::signupRoute(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    if(request.hasParam(":username") && request.hasParam(":password")) {
        std::string username = request.param(":username").as<std::string>();
        std::string password = request.param(":password").as<std::string>();
        std::cout << username << "," << password << std::endl;
        User user = User(username.c_str(), password.c_str());
        if(DatabaseService::insertUser(user)){
            response.send(Pistache::Http::Code::Ok, "User inserted successfully");
        } else {
            response.send(Pistache::Http::Code::Bad_Request, "Bad request");
        }
    }
}

void Server::loginRoute(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    if(request.hasParam(":username") && request.hasParam(":password")) {
        std::string username = request.param(":username").as<std::string>();
        std::string password = request.param(":password").as<std::string>();
        std::cout << username << "," << password << std::endl;
        User user = User(username.c_str(), password.c_str());
        User userRes = DatabaseService::getUser(user);
        std::cout << user._password() << ',' << user._username() << std::endl;
        // FIXME
        if(!userRes._username().compare(username) || !userRes._password().compare(password)){
            response.send(Pistache::Http::Code::Forbidden, "Access denied");
            return;
        }
        
        response.send(Pistache::Http::Code::Ok, "Access granted");
    }
}

void Server::listDirRoute(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::list<std::filesystem::directory_entry> files = FilesServices::listDirContent("/home/julianitow/");
    /*char* jsonStr = "{";
    for (const auto &file : files) {
        const char* path =         
    }*/
    response.send(Pistache::Http::Code::Ok, "Ok");
}

void Server::testAgainRoute(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    if(request.hasParam(":param")) {
        auto val = request.param(":param");
        int value = val.as<int>();
        std::cout << "Request param: " << value << std::endl;
    }
    response.send(Pistache::Http::Code::Ok, "Access testAgainRoute Success");
}

void Server::execInThread(Server* server, int thr) {
    server->init(thr);
    server->start();
}

User Server::createUser(const char* username, const char* password) {

}

void Server::shutdown(int signal) {
    Server::instance->httpEndpoint->shutdown();
    std::cout << "Server shutdown called on signal:" << signal << std::endl;
}

void Server::runMediaManager() {
    this->mediaManager = MediaManager();

    Library lib = Library();
    lib.addPath("/home/julianitow/Téléchargements");
    lib.scanForFiles();

}