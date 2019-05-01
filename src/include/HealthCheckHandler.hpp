/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: HealthCheckHandler.h
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */

#ifndef HEALTHCHECKHANDLER_H_
#define HEALTHCHECKHANDLER_H_

#include <pistache/endpoint.h>

/**
 * Handle Health Check requests.
 */
class HealthCheckHandler
{
public:
    void getHealthCheck(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response);
};
#endif