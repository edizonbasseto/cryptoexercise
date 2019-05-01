/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: KeyBusinessLogic.cpp
 * @Date: Wednesday, 1st May 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com>)
 */
#include <KeyBusinessLogic.hpp>

std::vector<unsigned long> SecretKey::calculateKey(const int numberGenerator,
        const int startPosition,
        const int jump,
        const int size)
{
    return sqrtCF(numberGenerator);
}

std::vector<unsigned long> SecretKey::sqrtCF(unsigned long D) {
    // sqrt(D) may be slightly off for large D.
    // If large D are expected, a correction for R is needed.
    unsigned long R = floor(sqrt(D));
    std::vector<unsigned long> f;
    f.push_back(R);
    if (R*R == D) {
        // Oops, a square
        return f;
    }
    unsigned long a = R, P = 0, Q = 1;
    do {
        P = a*Q - P;
        Q = (D - P*P)/Q;
        a = (R + P)/Q;
        f.push_back(a);
    }while(Q != 1);
    return f;
}