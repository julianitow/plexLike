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
    //FIXME Temporary for testing
    this->runMediaManager();
}

void Server::start() {
    this->httpEndpoint->setHandler(this->router.handler());
    this->httpEndpoint->serve();
}

void Server::setupRoutes() {
    using namespace Pistache::Rest;
    Routes::Get(this->router, "/signup/:username/:password", Routes::bind(&Server::signupRoute, this));
    Routes::Get(this->router, "/signin/:username/:password", Routes::bind(&Server::loginRoute, this));
    Routes::Get(this->router, "/libraries/:library/", Routes::bind(&Server::libraryContent, this));
    Routes::Get(this->router, "/libraries/:library/media/:media/stream", Routes::bind(&Server::streamRoute, this));
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
    //TODO if no parameters sent in request, response something
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

void Server::runMediaManager() {
    this->mediaManager = MediaManager();

    Library* movies = new Library("Movies");
    this->libraries.push_back(movies);
    movies->addPath("/media/julianitow/Samsung_T5/Films");
    movies->scanForFiles();
    
}

void Server::streamRoute(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    if(!request.hasParam(":library") && !request.hasParam(":media")) return;
    std::string library = request.param(":library").as<std::string>();
    std::string mediaTitle = request.param(":media").as<std::string>();
    std::string mediaPath;
    try {
        mediaTitle = mediaTitle.replace(mediaTitle.begin(), mediaTitle.end(), "%20", " ");
    } catch (std::system_error& err) {
        std::cerr << err.what() << std::endl;
    }
    std::cout << mediaTitle << std::endl;
    for (Library* lib : this->libraries) {
        if(lib->_name().compare(library) == 0) {
            for(Media media : lib->listMedia()) {
                std::cout << media._file().path().filename() << std::endl;
                //TODO Use of media title unsted of media file
                if(media._file().path().compare(mediaTitle) == 0){
                    response.send(Pistache::Http::Code::Found);
                }
            }
        }
    }

    response.send(Pistache::Http::Code::Ok);
}

void Server::libraryContent(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    if(request.hasParam(":library")) {
        std::string nameReq = request.param(":library").as<std::string>();
        for(Library* lib : this->libraries){
            std::cout << lib->_name() << std::endl;
            if(lib->_name().compare(nameReq) == 0) {
                //TODO json object with all contents of lib inside 
                nlohmann::json moviesJson;
                std::cout << lib->listMedia().size() << std::endl;
                for(Media media: lib->listMedia()) {
                    nlohmann::json mediaJson;
                    mediaJson["file"] = media._file().path();
                    moviesJson[media._file().path()] = mediaJson;
                }
                response.headers().add<Pistache::Http::Header::ContentType>("application/json");
                response.send(Pistache::Http::Code::Ok, moviesJson.dump());
            }
        }
    }
    response.send(Pistache::Http::Code::Bad_Request, "Missing library name");
}

void Server::shutdown(int signal) {
    Server::instance->httpEndpoint->shutdown();
    std::cout << "Server shutdown called on signal:" << signal << std::endl;
    exit(signal);
}