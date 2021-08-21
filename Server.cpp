#include "Server.h"

Server::Server(Pistache::Address addr) {
    this->httpEndpoint = std::make_shared<Pistache::Http::Endpoint>(addr);
}

void Server::init(size_t thr) {
    auto opts = Pistache::Http::Endpoint::options()
                                        .threads(static_cast<int>(thr));
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
}

void Server::testRoute(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Ok, "Access testRoute Success");
}

void Server::testAgainRoute(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    if(request.hasParam(":param")) {
        auto val = request.param(":param");
        int value = val.as<int>();
        std::cout << "Request param: " << value << std::endl;
    }
    response.send(Pistache::Http::Code::Ok, "Access testAgainRoute Success");
}
