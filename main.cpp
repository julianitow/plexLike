#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "Server.h"

int main() {
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(8080));
    
    int thr = 2;

    std::cout << "Cores = " << std::thread::hardware_concurrency() << std::endl;
    std::cout << "Using " << thr << " threads" << std::endl;

    Server server(addr);
    server.init(thr);
    server.start();
}