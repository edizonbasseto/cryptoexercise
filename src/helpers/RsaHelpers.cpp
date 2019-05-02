/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 *
 * @file: RsaHelpers.cpp
 * @Date: Wednesday, 1st May 2019
 * @author: Edizon Basseto Jr (edizon.basseto@wiboo.com.br>)
 */

#include <RsaHelpers.hpp>
#include <rsa.h>
#include <integer.h>

const std::string& RsaHelpers::getPrivateKey(Person p)
{
    return this->RSA_PRIVATE_KEY[p];
}

const std::string& RsaHelpers::getPublicKey(Person p)
{
    return this->RSA_PUBLIC_KEY[p];
}

const std::string& RsaHelpers::encryptRsa(const std::string& data, Person p)
{
    CryptoPP::RSA::PublicKey publicKey;

    try
    {
        CryptoPP::StringSource source(this->RSA_PUBLIC_KEY[p], true);
        CryptoPP::PEM_Load(source, publicKey);
    }
    catch(const CryptoPP::Exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    const CryptoPP::Integer& e = publicKey.GetPublicExponent();
    std:: cout << e << std::endl;
}

const std::string& RsaHelpers::decryptRsa(const std::string& data, Person p)
{

}