/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: randomhelpers.hpp
 * @Date: Sunday, 28th April 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com>)
 */

#ifndef __RANDOMHELPERS__
#define __RANDOMHELPERS__

#include <BaseInclude.hpp>
#include <cryptopp/osrng.h>
#include <cryptopp/secblock.h>
#include <hex.h>
#include <drbg.h>

/**
 * Essa classe contem métodos de ajuda para geração e validação de números
 * randomicos, com valores válidos para sistemas criptográficos.
 */
class RandomHelpers
{
public:
    /**
     * Gera uma palavra randomica baseado no tamanho fornecido.
     **/
    std::string getRandomWord(int size);
private:
    /**
     * Take a given ByteBlock and convert to string UTF8 value
     */
    std::string convertByteBlockToString(CryptoPP::SecByteBlock secBlock);
};

#endif