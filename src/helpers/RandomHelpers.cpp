/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: RandomHelpers.hpp
 * @Date: Sunday, 28th April 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com>)
 */

#include <RandomHelpers.hpp>

std::string RandomHelpers::getRandomWord(int size)
{
    // Veja explicações no README.
    CryptoPP::SecByteBlock entropy(48), result(size);
    CryptoPP::NonblockingRng prng;

    CryptoPP::RandomNumberSource rns(prng,
                                     entropy.size(),
                                     new CryptoPP::ArraySink(entropy, entropy.size()));

    CryptoPP::Hash_DRBG<CryptoPP::SHA256, 128/8, 440/8> drbg(entropy, 32, entropy+32, size);

    //RE-Seeding each generation will protect against Predictive Resistence(PR).
    prng.GenerateBlock(entropy, entropy.size());
    drbg.IncorporateEntropy(entropy, entropy.size());
    drbg.GenerateBlock(result, size); //All this is in bytes. So, the size is bytes.
                                      //CryptoPP convert each char (1 byte) to HEX.
                                      //Hex is one byte but two numbers. Ex: 61 is a.
                                      //Within that, the result will always have twice the size requested.

    return this->convertByteBlockToString(result).substr(0, size);
}

std::string RandomHelpers::convertByteBlockToString(CryptoPP::SecByteBlock byteBlock)
{
    std::string word;
    CryptoPP::HexEncoder hex(new CryptoPP::StringSink(word));
    hex.Put(byteBlock, byteBlock.size());
    hex.MessageEnd();

    return word;
}