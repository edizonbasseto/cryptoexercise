/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: ScramblerEndpoint.cpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#include <HealthCheckHandler.hpp>
#include <ScramblerHandler.hpp>
#include <pistache/router.h>
#include <pistache/endpoint.h>

using namespace Pistache;
using namespace Rest;
using namespace std;

/**
 * This class will provide all configuration for endpoints on the API Rest server.
 */
class ScramblerEndpoint
{
public:
    ScramblerEndpoint(Pistache::Address addr, std::string &dir);
    // Will start the REST Endpoint with 2 threads.
    void init(size_t thr = 2);
    //Serving....
    void start();
    void shutdown();
    ~ScramblerEndpoint();
private:

    /**
     * Configure routes and it's handlers.
     */
    void setupRoutes();

    std::string schemasdir;
    Pistache::Address _addr;

    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Rest::Router router;
    HealthCheckHandler *healthCheckHandler = new HealthCheckHandler();
    ScramblerHandler *scramblerHandler;

};
