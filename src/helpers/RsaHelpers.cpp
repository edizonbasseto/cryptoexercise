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
#include <base64.h>
#include <assert.h>
#include <hex.h>

RsaHelpers::RsaHelpers(){}

const std::string RsaHelpers::PRV_HEADER("-----BEGIN RSA PRIVATE KEY-----");
const std::string RsaHelpers::PRV_FOOTER("-----END RSA PRIVATE KEY-----");

const std::string RsaHelpers::PUB_HEADER("-----BEGIN PUBLIC KEY-----");
const std::string RsaHelpers::PUB_FOOTER("-----END PUBLIC KEY-----");

const std::string& RsaHelpers::getPEMPrivateKey(Person p)
{
    return this->RSA_PRIVATE_KEY[p];
}

const std::string& RsaHelpers::getPEMPublicKey(Person p)
{
    return this->RSA_PUBLIC_KEY[p];
}

void RsaHelpers::getCryptoPrivateKey(CryptoPP::RSA::PrivateKey& key, Person p)
{
    size_t pos1, pos2;
    pos1 = this->getPEMPrivateKey(p).find(PRV_HEADER);

    if(pos1 == std::string::npos)
        throw std::runtime_error("PEM header not found");

    pos2 = this->getPEMPrivateKey(p).find(PRV_FOOTER, pos1+1);

    if(pos2 == std::string::npos)
        throw std::runtime_error("PEM footer not found");

    // Start position and length
    pos1 = pos1 + PRV_HEADER.length();
    pos2 = pos2 - pos1;
    std::string keystr = this->getPEMPrivateKey(p).substr(pos1, pos2);

    // Base64 decode, place in a ByteQueue
    CryptoPP::ByteQueue queue;
    CryptoPP::Base64Decoder decoder;

    decoder.Attach(new CryptoPP::Redirector(queue));
    decoder.Put((const CryptoPP::byte*)keystr.data(), keystr.length());
    decoder.MessageEnd();

    try
    {
        key.BERDecodePrivateKey(queue, false /*paramsPresent*/, queue.MaxRetrievable());

        // BERDecodePrivateKey is a void function. Here's the only check
        // we have regarding the DER bytes consumed.
        assert(queue.IsEmpty());
        return;
    }
    catch (const CryptoPP::Exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        throw ex;
    }
}

void RsaHelpers::getCryptoPublicKey(CryptoPP::RSA::PublicKey& key, Person p)
{
    size_t pos1, pos2;
    pos1 = this->getPEMPublicKey(p).find(PUB_HEADER);

    if(pos1 == std::string::npos)
        throw std::runtime_error("PEM header not found");

    pos2 = this->getPEMPublicKey(p).find(PUB_FOOTER, pos1+1);

    if(pos2 == std::string::npos)
        throw std::runtime_error("PEM footer not found");

    // Start position and length
    pos1 = pos1 + PUB_HEADER.length();
    pos2 = pos2 - pos1;
    std::string keystr = this->getPEMPublicKey(p).substr(pos1, pos2);

    // Base64 decode, place in a ByteQueue
    CryptoPP::ByteQueue queue;
    CryptoPP::Base64Decoder decoder;

    decoder.Attach(new CryptoPP::Redirector(queue));
    decoder.Put((const CryptoPP::byte*)keystr.data(), keystr.length());
    decoder.MessageEnd();

    try
    {
        key.Load(queue);
        assert(queue.IsEmpty());
        return;
    }
    catch (const CryptoPP::Exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        throw ex;
    }
}

CryptoPP::AutoSeededRandomPool& RsaHelpers::rng_get() {
    static CryptoPP::AutoSeededRandomPool defRng;
    return defRng;
}

const std::string RsaHelpers::encryptRsa(const std::string& data, Person p)
{
    std::string cipher;
    std::string output;

    CryptoPP::RSA::PublicKey pk = CryptoPP::RSA::PublicKey();
    this->getCryptoPublicKey(pk, p);
    CryptoPP::RSAES_OAEP_SHA_Encryptor rsaEnc( pk );

    CryptoPP::StringSource ss1(data, true,
        new CryptoPP::PK_EncryptorFilter( rng_get(), rsaEnc,
            new CryptoPP::StringSink( cipher )
    ));

    CryptoPP::byte bytes[cipher.size()];

	for (int i = 0; i < cipher.size(); i++) {
        bytes[i] = static_cast<CryptoPP::byte>(cipher[i]);
	}

    CryptoPP::StringSource ss(bytes, sizeof(bytes), true,
        new CryptoPP::HexEncoder(
            new CryptoPP::StringSink(output)
    ));

    return output;
}

const std::string RsaHelpers::decryptRsa(const std::string& cipher, Person p)
{
    std::string bytes;

    CryptoPP::StringSource ss(cipher, true,
        new CryptoPP::HexDecoder(
            new CryptoPP::StringSink(bytes)));

    std::string saida;
    CryptoPP::AutoSeededRandomPool rng;

    CryptoPP::RSA::PrivateKey pk = CryptoPP::RSA::PrivateKey();
    this->getCryptoPrivateKey(pk, p);

    CryptoPP::RSAES_OAEP_SHA_Decryptor d(pk);
    CryptoPP::StringSource( bytes, true, new CryptoPP::PK_DecryptorFilter(rng, d, new CryptoPP::StringSink( saida )));

    return saida;
}