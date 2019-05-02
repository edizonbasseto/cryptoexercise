/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: KeyBusinessLogic.cpp
 * @Date: Wednesday, 1st May 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com>)
 */
#include <KeyBusinessLogic.hpp>

const long int SecretKey::calculateKey(const int numberGenerator,
                                       const int startPosition,
                                       const int jump,
                                       const int size)
{
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
    std::cout << "Tithe: " << tithe << std::endl;

    int control = startPosition-1;
    for (int i=0; i<tithe.length(); i++)
    {
        if (control == i)
        {
            key += tithe[i];

            control += jump;
        }
    }

    std::cout << "Selected numbers: " << key << std::endl;

    return 0;
}

void SecretKey::dumpLinearForm(const ContinuedFractionForm_t& a) {
   std::cout << "Dump Linear Form " << std::endl;

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