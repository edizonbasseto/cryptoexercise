/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: HealthCheckHandler.cpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */


#include <HealthCheckHandler.hpp>

void HealthCheckHandler::getHealthCheck(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response)
{
    UNUSED(request);
    response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
    response.send(Pistache::Http::Code::Ok, "{status: OK}");
}
