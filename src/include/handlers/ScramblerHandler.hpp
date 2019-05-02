/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: ScramblerHandler.hpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#ifndef SCRAMBLERHANDLER_H_
#define SCRAMBLERHANDLER_H_
#include <ScramblerSliceResponse.hpp>
#include <ScramblerSliceRequest.hpp>
#include <DescramblerSliceRequest.hpp>
#include <DescramblerSliceResponse.hpp>
#include <SliceBusiness.hpp>
#include <cstdio>
#include <string>
#include <exception>
#include <typeinfo>
#include <stdexcept>
#include <pistache/endpoint.h>
#include <rapidjson/schema.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <ctime>

/**
 * Handle all REST requests of /scrambler REST endpoint
 */
class ScramblerHandler
{
public:
    ScramblerHandler(std::string &dir);
    void processSlice(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response);
    void joinSlice(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response);
    ~ScramblerHandler();

private:
    std::atomic<uint_fast64_t> requestNumber;
    rapidjson::Document schemaRecoverKeyRequest;
    rapidjson::Document schemaSliceRequest;
    SliceBusiness sliceBusiness;
    std::string schemasdir;

    std::string preparePath(const std::string file);

    /**
     * Recover the Slice request json schema
     */
    void loadSchemaSliceRequest();

    /**
     * Recover the key request json schema
     */
    void loadSchemaRecoverKeyRequest();

    /**
     * Read all the json schemas files. This is loaded at constructor, so will avoid multiple IOs.
     */
    void loadSchemaFiles();

    /**
     * Check a JSON based on the given validator
     */
    void validateData(rapidjson::Document& d, rapidjson::SchemaValidator& validator);


    rapidjson::Document createDocumentFromString(const std::string body);

    /**
     * Validate if the payload is accordingly to the specification
     */
    void validateSliceRequest(const std::string body);

    /**
     * Validate if the payload is accordingly to the specification
     */
    void validateRecoverKeyRequest(const std::string body);

    /**
     * Prints a request received messaged on the screen
     */
    void printRequestDateTime();
};
#endif