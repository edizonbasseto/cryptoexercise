/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: KeyBusinessLogic.cpp
 * @Date: Wednesday, 1st May 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com>)
 */
#include <KeyBusinessLogic.hpp>
#include <hex.h>

///////////////////////////////////////////////////////
//// SECRET VALUE                                  ////
///////////////////////////////////////////////////////
const std::string SecretValue::encryptSecretValue(const SecretValueProtocol& secretValue,
                                                  RsaHelpers::Person personFrom,
                                                  RsaHelpers::Person personTo)
{
    std::string scrtValue = std::to_string(secretValue.startPosition) + PALAVRA_DELIMITADOR +
                            std::to_string(secretValue.jump) + PALAVRA_DELIMITADOR +
                            std::to_string(secretValue.garbageTerminatorSize) + PALAVRA_DELIMITADOR +
                            secretValue.garbageTeminator + PALAVRA_DELIMITADOR +
                            std::to_string(secretValue.numberGenerator) + PALAVRA_DELIMITADOR +
                            std::to_string(personFrom);

    prepareSecretValue(scrtValue);
    return RsaHelpers::getInstance().encryptRsa(scrtValue, personTo);
}
void SecretValue::prepareSecretValue(std::string& secretValueStr)
{
    //Create the check sum over this payload.
    CryptoPP::SHA256 hash;
    std::string digest;
    CryptoPP::StringSource s(secretValueStr,
                             true,
                             new CryptoPP::HashFilter(hash,
                                                      new CryptoPP::HexEncoder(
                                                      new CryptoPP::StringSink(digest))));
    std::cout << std::endl << "Checksum Gerado...." << digest;

    secretValueStr += PALAVRA_DELIMITADOR + digest;
}

void SecretValue::validateSecretValue(SecretArray_t dataArr,
                                      RsaHelpers::Person personFrom,
                                      RsaHelpers::Person personTo)
{
    std::cout << std::endl << "Validando payload recebido...";

    if (dataArr.size() < POSICAO_CHECKSUM ||
        dataArr[POSICAO_USERFROM] != std::to_string(personFrom))
    {
        throw "You are not my sender!!!!!!";
    }

    const std::string hashSent = dataArr[POSICAO_CHECKSUM];

    std::string data = "";

    for(int i=0; i<dataArr.size()-1; i++)
    {
        data += dataArr[i];

        if (i+1 != dataArr.size()-1)
        {
            data += ";";
        }
    }
    std::cout << std::endl << std::endl << data;

    CryptoPP::SHA256 hash;
    std::string digest;
    CryptoPP::StringSource s(data,
                             true,
                             new CryptoPP::HashFilter(hash,
                                                      new CryptoPP::HexEncoder(
                                                      new CryptoPP::StringSink(digest))));

    if (0 != digest.compare(hashSent))
    {
        throw "Esse dado foi modificado e não poderá ser processado.";
    }

    dataArr[POSICAO_CHECKSUM] = digest;

    std::cout << std::endl << "Dado validado pela pessoa " << std::to_string(personTo) << std::endl;
}
const SecretValueProtocol SecretValue::decodeSecretValue(const std::string& encodedSecretValue,
                                                         RsaHelpers::Person personFrom,
                                                         RsaHelpers::Person personTo)
{

    std::string dado = RsaHelpers::getInstance().decryptRsa(encodedSecretValue, personTo);
    SecretArray_t tempVector;

    std::cout << dado << std::endl;
    // THERE IS NO SPLIT !!!!!! :(
    size_t pos = 0;
    std::string token;
    while ((pos = dado.find(PALAVRA_DELIMITADOR.c_str())) != std::string::npos) {
        token = dado.substr(0, pos);
        tempVector.push_back(token);
        dado.erase(0, pos + 1);
    }
    tempVector.push_back(dado);
    validateSecretValue(tempVector, personFrom, personTo);

    return SecretValueProtocolBuilder::buildProtocol(tempVector);
}

///////////////////////////////////////////////////////
///// SECRET VALUE PROTOCOL BUILDER                ///
//////////////////////////////////////////////////////
const SecretValueProtocol SecretValueProtocolBuilder::buildProtocol(
    int startPosition,
    int jump,
    int garbageTerminatorSize,
    std::string garbageTeminator,
    int numberGenerator)
{
    SecretValueProtocol prot {startPosition, jump, garbageTerminatorSize,
                              garbageTeminator, numberGenerator};

    validateProtocolData(prot);

    return prot;
}

const SecretValueProtocol SecretValueProtocolBuilder::buildProtocol(const std::vector<std::string>& dataArr)
{
    if (dataArr.empty())
    {
        throw "Data Array is not correct.";
    }

    return buildProtocol(
        stoi(dataArr[0]),
        stoi(dataArr[1]),
        stoi(dataArr[2]),
        dataArr[3],
        stoi(dataArr[4])
    );
}

void SecretValueProtocolBuilder::validateProtocolData(SecretValueProtocol& valueProtocolData)
{
    if (valueProtocolData.startPosition <= 0)
    {
        throw "Start position must be positive and greater than zero.";
    }

    if (valueProtocolData.jump < 0)
    {
        throw "Jump must be greater than zero.";
    }
}

///////////////////////////////////////////////////////
//// SECRET KEY                                     ///
///////////////////////////////////////////////////////
const std::string SecretKey::calculateKey(const int numberGenerator,
                                          const int startPosition,
                                          const int jump,
                                          const int size)
{
    std::cout << std::endl << std::endl
              << "**** CALCULO DA CHAVE *****" << std::endl;

    std::string key = "";
    dumpLinearForm(sqrtCF(numberGenerator));

    int bitsPrecision = (startPosition + (jump*size))*4;
    mpf_t res,generator;
    mpf_set_default_prec(bitsPrecision);

    mpf_init(res);
    mpf_init(generator);

    mpf_set_str(generator, std::to_string(numberGenerator).c_str(), 10);
    mpf_sqrt (res, generator);

    std::stringstream str;
    str << std::setprecision(bitsPrecision) << res;
    std::string tithe = str.str().substr(str.str().find(".")+1, str.str().length());

    std::cout << "Full Calculated number: " << str.str() << std::endl;
    std::cout << "Tithe                 : " << tithe << std::endl;

    int control = startPosition-1;
    int limit = tithe.length() > size ? size : tithe.length();

    for (int i=0; i<tithe.length(); i++)
    {
        if (control == i)
        {
            key += tithe[i];
            control += jump;
        }
    }
    std::cout << "Selected numbers      : " << key.substr(0, limit) << std::endl;
    return key.substr(0, limit);
}

void SecretKey::dumpLinearForm(const ContinuedFractionForm_t& a) {
   std::cout << "Fração Continua - Representação LINEAR! " << std::endl;

    for(int i=0; i < a.size(); i++)
        std::cout << std::setprecision(30) << a.at(i) << ' ';

   std::cout << std::endl << "-------------" << std::endl;
}


const ContinuedFractionForm_t SecretKey::sqrtCF(unsigned long D) {
    // sqrt(D) may be slightly off for large D.
    // If large D are expected, a correction for R is needed.
    unsigned long R = floor(sqrt(D));

    std::vector<unsigned long> f;
    f.push_back(R);

    if (R*R == D) {
        throw "NAO PODE USAR NUMERO QUADRADO PERFEITO!!!!!!!!";
    }

    unsigned long a = R, P = 0.0, Q = 1.0;
    do {
        P = a*Q - P;
        Q = floor((D - P*P)/Q);
        a = floor((R + P)/Q);
        f.push_back(a);
    }while(Q != 1);

    return f;
}