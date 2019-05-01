/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: ScramblerEndpoint.cpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#include <ScramblerEndpoint.hpp>

ScramblerEndpoint::ScramblerEndpoint(Pistache::Address addr, std::string &dir)
{
    this->_addr = addr;
    this->httpEndpoint = std::make_shared<Http::Endpoint>(addr);
    this->schemasdir = dir;
    this->scramblerHandler = new ScramblerHandler(schemasdir);
}

void ScramblerEndpoint::init(size_t thr)
{
    //Tcp::Options::InstallSignalHandler |
    auto opts = Http::Endpoint::options()
        .threads(thr)
        .flags(Tcp::Options::ReuseAddr);

    httpEndpoint->init(opts);
    setupRoutes();
}

void ScramblerEndpoint::start()
{
    httpEndpoint->setHandler(router.handler());
    cout << "Accepting requests on port " << _addr.port().toString() << " now. SIG TERM are blocked." << endl;
    httpEndpoint->serve();
}

void ScramblerEndpoint::shutdown()
{
    httpEndpoint->shutdown();
}

ScramblerEndpoint::~ScramblerEndpoint()
{
    delete this->httpEndpoint.get();
    delete this->healthCheckHandler;
    delete this->scramblerHandler;
    this->_addr = nullptr;
}

void ScramblerEndpoint::setupRoutes() {
    Routes::Get(router, "/healthcheck", Routes::bind(&HealthCheckHandler::getHealthCheck, healthCheckHandler));
    Routes::Post(router, "/scrambler/slice", Routes::bind(&ScramblerHandler::processSlice, scramblerHandler));
    Routes::Post(router, "/scrambler/joinslices", Routes::bind(&ScramblerHandler::joinSlice, scramblerHandler));
}
