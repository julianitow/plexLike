#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

class Server {
    private:
        std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
        Pistache::Rest::Router router;

        void setupRoutes();
        void testRoute(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
        void testAgainRoute(const Pistache::Rest::Request&, Pistache::Http::ResponseWriter);
    public:
        Server(Pistache::Address);
        void init(size_t = 2);
        void start();
};