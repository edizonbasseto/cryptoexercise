/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: ScramblerHander.cpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */

#include <ScramblerHandler.hpp>
#include <iomanip>

ScramblerHandler::ScramblerHandler(std::string &dir)
{
    requestNumber = 0;
    this->schemasdir = dir;
    this->loadSchemaFiles();
}

void ScramblerHandler::joinSlice(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response)
{
    try
    {
        printRequestDateTime();
        if (request.body().empty())
        {
            throw "Body is empty";
        }

        this->validateRecoverKeyRequest(request.body());

        nlohmann::basic_json<> jInput = nlohmann::basic_json<>::parse(request.body());
        nlohmann::basic_json<> resp = this->sliceBusiness.DescrambleData(jInput.get<Schemas::DescramblerSliceRequest>());

        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
        response.send(Pistache::Http::Code::Ok, resp.dump());
    }
    catch(char const* msg)
    {
        std::string str(msg);
        std::string payload("{ \"error\":\"" + str + "\"}");

        response.send(Pistache::Http::Code::Bad_Request, payload);
    }
    catch(...)
    {
        std::exception_ptr p = std::current_exception();
        std::clog <<(p ? p.__cxa_exception_type()->name() : "null") << std::endl;
        response.send(Pistache::Http::Code::Internal_Server_Error, (p ? p.__cxa_exception_type()->name() : "null"));
    }
}

void ScramblerHandler::printRequestDateTime()
{
    requestNumber++;
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::cout << "SCRAMBLER-["
              << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X")
              << "]-Received the request number "
              << requestNumber
              << "."
              << std::string(10, ' ')
              <<"\r" << std::flush;
}

void ScramblerHandler::processSlice(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response)
{
    try
    {
        printRequestDateTime();
        if (request.body().empty())
        {
            throw "Body is empty";
        }

        this->validateSliceRequest(request.body());

        nlohmann::basic_json<> jInput = nlohmann::basic_json<>::parse(request.body());
        nlohmann::basic_json<> resp = this->sliceBusiness.scrambleData(jInput.get<Schemas::ScramblerSliceRequest>());

        response.headers().add<Pistache::Http::Header::ContentType>(MIME(Application, Json));
        response.send(Pistache::Http::Code::Ok, resp.dump());
    }
    catch(char const* msg)
    {
        std::string str(msg);
        std::string payload("{ \"error\":\"" + str + "\"}");

        response.send(Pistache::Http::Code::Bad_Request, payload);
    }
    catch(...)
    {
        std::exception_ptr p = std::current_exception();
        std::clog <<(p ? p.__cxa_exception_type()->name() : "null") << std::endl;
        response.send(Pistache::Http::Code::Internal_Server_Error, (p ? p.__cxa_exception_type()->name() : "null"));
    }

}

ScramblerHandler::~ScramblerHandler()
{
    this->schemaRecoverKeyRequest = nullptr;
    this->schemaSliceRequest = nullptr;
    this->sliceBusiness.~SliceBusiness();
};

void ScramblerHandler::validateRecoverKeyRequest(const std::string body)
{
    rapidjson::Document d = this->createDocumentFromString(body);

    rapidjson::SchemaDocument schema(this->schemaRecoverKeyRequest);
    rapidjson::SchemaValidator validator(schema);

    this->validateData(d, validator);
}

void ScramblerHandler::validateSliceRequest(const std::string body)
{
    rapidjson::Document d = this->createDocumentFromString(body);

    rapidjson::SchemaDocument schema(this->schemaSliceRequest);
    rapidjson::SchemaValidator validator(schema);

    this->validateData(d, validator);
}

rapidjson::Document ScramblerHandler::createDocumentFromString(const std::string body)
{
    rapidjson::Document d;
    if (d.Parse(body.c_str()).HasParseError()) {
        throw "The body of the request is not a JSON.";
    }

    return d;
}

/**
 * Check a JSON based on the given validator
 */
void ScramblerHandler::validateData(rapidjson::Document& d, rapidjson::SchemaValidator& validator)
{
    if (!d.Accept(validator))
    {
        throw "JSON is not according to the json schema defined.";
    }
}

/**
 * Read all the json schemas files. This is loaded at constructor, so will avoid multiple IOs.
 */
void ScramblerHandler::loadSchemaFiles()
{
    if(!this->schemasdir.empty())
    {
        std::cout << "Reading schemas files from: " << this->schemasdir << std::endl;
    }
    else
    {
        std::cout << "Reading schemas files from: ./jsonSchemas/" << std::endl;
    }
    try
    {
        this->loadSchemaRecoverKeyRequest();
        this->loadSchemaSliceRequest();
    }
    catch(const std::exception& e)
    {
        std::cout << "Impossible to load JSON schemas files." << std::endl;
        std::cerr << e.what() << std::endl;
        throw e;
    }


}

std::string ScramblerHandler::preparePath(const std::string file)
{
    std::string pathbase = "./jsonSchemas/";
    if(!this->schemasdir.empty())
    {
        pathbase = this->schemasdir;
        if(*pathbase.rend() != '/')
        {
            pathbase += "/";
        }
    }
    return pathbase + file;
}
/**
 * Recover the key request json schema
 */
void ScramblerHandler::loadSchemaRecoverKeyRequest()
{
    std::ifstream ifs(this->preparePath("scrambler.recover.key.request.json"));
    rapidjson::IStreamWrapper isw(ifs);

    if (schemaRecoverKeyRequest.ParseStream(isw).HasParseError()) {
        throw "Impossible to parse JSON Validator. System cannot continue.";
    }

    if(ifs.is_open())
    {
        ifs.close();
    }
}

/**
 * Recover the Slice request json schema
 */
void ScramblerHandler::loadSchemaSliceRequest()
{
    std::ifstream ifs(this->preparePath("scrambler.slice.request.json"));
    rapidjson::IStreamWrapper isw(ifs);

    if (schemaSliceRequest.ParseStream(isw).HasParseError()) {
        throw "Impossible to parse JSON Validator. System cannot continue.";
    }

    if(ifs.is_open())
    {
        ifs.close();
    }
}