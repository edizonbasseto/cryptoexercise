/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: KeyBusinessLogic.cpp
 * @Date: Wednesday, 1st May 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com>)
 */

#include <MessageBusinessLogic.hpp>
#include <KeyBusinessLogic.hpp>
#include <RandomHelpers.hpp>
#include <functional>
#include <random>
#include <cryptopp/osrng.h>
#include <base64.h>

const void MessageBusinessLogic::encryptMessage(std::string& message, const SecretValueProtocol& protocol)
{
    //Recovering the key.
    const std::string secretKey = SecretKey::calculateKey(
        protocol.numberGenerator,
        protocol.startPosition,
        protocol.jump,
        message.size());

    std::mt19937::result_type seed = time(0);
    auto dice_rand = std::bind(std::uniform_int_distribution<int>(48,100),
                               std::mt19937(seed));

    int garbagesize = dice_rand();

    std::cout << std::endl << " -Tamanho do Lixo Esquerdo: " << garbagesize << std::endl;

    std::string leftGarbage = RandomHelpers::getInstance().getRandomWord(garbagesize);
    std::string rigthGarbage = "";

    for(int i=0; i<protocol.garbageTerminatorSize; i++)
    {
        leftGarbage.append(protocol.garbageTeminator);
        rigthGarbage.append(protocol.garbageTeminator);
    }

    garbagesize = dice_rand();
    std::cout << " -Tamanho do Lixo Direito: " << garbagesize << std::endl << std::endl;
    rigthGarbage += RandomHelpers::getInstance().getRandomWord(garbagesize);

    scrambleData(message, secretKey);

    message = leftGarbage + message + rigthGarbage;
}

const void MessageBusinessLogic::decryptMessage(std::string& scrambledMessage, const SecretValueProtocol& protocol)
{
    removeGarbage(scrambledMessage, protocol);

    std::string texto;
    base64ToString(texto, scrambledMessage);

    std::cout << "A mensagem recebida foi: " << std::endl
              << " Tamanho: " << texto.size() << std::endl
              << " > " << texto;

    //Recovering the key.
    const std::string secretKey = SecretKey::calculateKey(
        protocol.numberGenerator,
        protocol.startPosition,
        protocol.jump,
        texto.size());

    scrambleData(texto, secretKey);
    scrambledMessage.clear();
    base64ToString(scrambledMessage, texto);

    std::cout << "Decrypt concluído." << std::endl << std::endl;
}

const void MessageBusinessLogic::removeGarbage(std::string& scrambledMessage, const SecretValueProtocol& protocol)
{
    std::string terminator = "";
    for(int i=0; i< protocol.garbageTerminatorSize; i++)
    {
        terminator.append(protocol.garbageTeminator);
    }

    int leftPos = scrambledMessage.find(std::string(terminator)) + terminator.size();

    scrambledMessage.erase(0, leftPos);

    int rightPos = scrambledMessage.find(std::string(terminator));

    scrambledMessage.erase(rightPos, scrambledMessage.size());

    std::cout << "Lixo removido da mensagem." << std::endl
              << " - Terminator procurado       : " << terminator << std::endl
              << " - Lixo Esquerdo encontrado em: " << leftPos << std::endl
              << " - Lixo Direito encontrado em : " << rightPos << std::endl
              << " - Mensagem limpa             : " << scrambledMessage << std::endl;

}

const void MessageBusinessLogic::scrambleData(std::string& message, const std::string& secretKey)
{

    boost::dynamic_bitset<unsigned char> messageBit(message.begin(), message.end());
    boost::dynamic_bitset<unsigned char> keyBit(secretKey.begin(), secretKey.end());

    boost::dynamic_bitset<unsigned char> newValue = messageBit ^ keyBit;

    std::cout << "Embaralhando os dados." << std::endl
              << " Chave     : " << keyBit     << " Tamanho original da chave   : " << secretKey.size() << std::endl
              << " Mensagem  : " << messageBit << " Tamanho original da mensagem: " << message.size() << std::endl
              << " Novo Valor: " << newValue << std::endl;

    bitSetToBase64(message, newValue);
    message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
    std::cout << " Mensagem embaralhada (STR): " << message << std::endl;
}

const void MessageBusinessLogic::bitSetToBase64(std::string& mesageBase64,const boost::dynamic_bitset<unsigned char>& bits)
{
    mesageBase64.clear();
    CryptoPP::byte bytes[bits.num_blocks()];
    boost::to_block_range(bits, bytes);

    CryptoPP::StringSource ss(bytes, sizeof(bytes), true,
        new CryptoPP::Base64Encoder(
            new CryptoPP::StringSink(mesageBase64)
        )
    );
}

const void MessageBusinessLogic::base64ToString(std::string& message,const std::string& base64)
{
    CryptoPP::StringSource ss(base64, true,
        new CryptoPP::Base64Decoder(
            new CryptoPP::StringSink(message)
        )
    );
}
