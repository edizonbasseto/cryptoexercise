/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: KeyBusinessLogic.cpp
 * @Date: Wednesday, 1st May 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com>)
 */
#ifndef __KEY_BUSINESS_LOGIC_H__
#define __KEY_BUSINESS_LOGIC_H__

#include <BaseInclude.hpp>
#include <array>
#include <vector>
#include <sstream>
#include <iterator>
#include <cmath>
#include <iomanip>
#include <tuple>
#include <limits>
#include <gmp.h>

typedef std::array<std::string, 5> ProtocolArray_t;
typedef std::vector<unsigned long int> ContinuedFractionForm_t;

/**
 * All the logic reggarding decryption/encrpytion of secret value.
 */
class SecretValue
{
public:
    /**
     * Receive the RSA encrypted secret value, decrypt it, and
     * read the protocol accordingly.
     */
    static const ProtocolArray_t& decodeSecretValue(const std::string secretValue);

    /**
     * Encrypt a secret value with RSA
     **/
    static const std::string encryptSecretValue(const ProtocolArray_t& secretValue);

};

/**
 * Logics reggarding Secret Key, like calculation based on the given number
 */
class SecretKey
{
    public:
        /**
         * Calculate the Secret Key
         *
         * @param numberGenerator the number to be used on a continued fraction calculation.
         * @param startposition the initial position to retrieve a numbef fomr continued fraction.
         * @param jump how many jumps to take a single value
         * @param size: the message size, meaning, how many values must be retrieved.
         */
        const static long int calculateKey(const int numberGenerator,
                                           const int startPosition,
                                           const int jump,
                                           const int size);
    private:
        /**
         * Get the linear form of a continued fraction.
         * https://stackoverflow.com/questions/12182701/generating-continued-fractions-for-square-roots
         *
         **/
        const static ContinuedFractionForm_t sqrtCF(unsigned long D);

        /**
         * Now calculate the Sum of values, bases on the control numbers has informed.
         **/
        const static long int calculateCF(const ContinuedFractionForm_t& D,
                                          const int startPosition,
                                          const int jump,
                                          const int size);

        static void dumpLinearForm(const ContinuedFractionForm_t& D);
        static void dumpSumResult(const std::vector<long double>& D);
};

/**
 * The secret value protocol.
 * The protocol is composed by:
 *  - start position: where to start to retrieve the secret key.
 *  - jump: how many positions to jump to compose the secret key.
 *  - garbage terminator size: how many times a terminator must be found to be considered as terminator.
 *  - garbage terminator: the garbage terminator.
 *  - numberGenerator: the number to be used to calculate the secret key.
 */
struct SecretValueProtocol
{
    int startPosition;
    int jump;
    int garbageTerminatorSize;
    char garbageTeminator;
    int numberGenerator;
};

/**
 * Apply the necessary validations over a Secret Value protocol
 * before creating the array.
 * Also, get an Array and transform in a protocol structure.
 */
class SecretValueProtocolBuilder
{
public:
    /**
     * Generate an array from all protocol data
     **/
    const ProtocolArray_t& buildProtocolToArray(SecretValueProtocol& valueProtocolData);
    const SecretValueProtocol& buildProtocolFromArray(ProtocolArray_t& protocolArray);

private:
    void validateProtocolData(SecretValueProtocol& valueProtocolData);
};

#endif