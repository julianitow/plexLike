#include <csignal>
#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "Server.h"

int main() {

    signal(SIGINT, Server::shutdown);
    signal(SIGABRT, Server::shutdown);
    signal(SIGTERM, Server::shutdown);
    
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(8080));
    int thr = 2;

    std::cout << "Cores = " << std::thread::hardware_concurrency() << std::endl;
    std::cout << "Using " << thr << " threads" << std::endl;

    Server* server = Server::getInstance(addr);
    server->init(thr);
    try {
        server->start();
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
    }
}