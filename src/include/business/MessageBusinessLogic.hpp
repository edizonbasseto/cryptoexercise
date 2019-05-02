/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: KeyBusinessLogic.cpp
 * @Date: Wednesday, 1st May 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com>)
 */

#ifndef __MESSAGE_BUSINESS_LOGIC_H__
#define __MESSAGE_BUSINESS_LOGIC_H__

#include <BaseInclude.hpp>
#include <KeyBusinessLogic.hpp>
#include <bitset>
#include <fstream>
#include <cstdlib>
#include <boost/dynamic_bitset.hpp>

class MessageBusinessLogic
{
public:
    /**
     * Based on the protocol, encrypt the message
     **/
    static const void encryptMessage(std::string& message, const SecretValueProtocol& protocol);

    /**
     * Based on the protocol, decrypt the message
     **/
    static const void decryptMessage(std::string& scrambledMessage, const SecretValueProtocol& protocol);

private:

    /**
     * Transforma uma mensagem embaralhada em uma string BASE 64
     **/
    static const void bitSetToBase64(std::string& mesageBase64,const boost::dynamic_bitset<unsigned char>& bits);

    /**
     * Transforma uma mensagem BASE64 em um texto UTF-8
     **/
    static const void base64ToString(std::string& mesage,const std::string& base64);

    /**
     * Embaralha a mensagem com a chave calculada.
     **/
    static const void scrambleData(std::string& message, const std::string& secretKey);

    /**
     * Desembaralha a mensagem com a chave calculada.
     **/
    static const void descrambleData(std::string& message, const std::string& secretKey);

    /**
     * Remove o lixo da mensagem scrambled baseado no protocolo informado.
     **/
    static const void removeGarbage(std::string& scrambledMessage, const SecretValueProtocol& protocol);
};

#endif
