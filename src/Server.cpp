/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: server.cpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */

#include <ScramblerEndpoint.hpp>
#include <RandomHelpers.hpp>
#include <KeyBusinessLogic.hpp>
#include <RsaHelpers.hpp>

void drawHeaderMessage(int threads)
{
    cout << "**************************" << std::endl;
    cout << "**** Cripto Method   *****" << std::endl;
    cout << "**************************" << std::endl;
    cout << "** Cores = " << hardware_concurrency();
    if(hardware_concurrency() < 10)
    {
        cout << "            **" << endl;
    }
    else
    {
        cout << "           **" << endl;
    }
    cout << "** Using " << threads << " threads";
    if(hardware_concurrency() < 10)
    {
        cout << "      **" << endl;
    }
    else
    {
        cout << "     **" << endl;
    }
    cout << "**************************" << std::endl;
}

int main(int argc, char * argv[])
{

    //Pistache::Address addr(Pistache::Ipv4::loopback(), Pistache::Port(9080));
    int thr = std::thread::hardware_concurrency();
    drawHeaderMessage(thr);

    //Get the JSON Schemas directory.
    //If not informed will get the default ./jsonSchemas directory.
    std::string schemasdir("");
    long i = 0;
    if (argc > 1)
    {
        schemasdir = std::string (argv[1]);
        i = std::atol(schemasdir.c_str());
    }

    RandomHelpers randomHelpers = RandomHelpers();

     std::string x = RsaHelpers::getInstance().encryptRsa("XXXXXXXXXX", RsaHelpers::PERSON1);

     std::cout << x << std::endl;

     std::string y = RsaHelpers::getInstance().decryptRsa(x, RsaHelpers::PERSON1);

     std::cout << y << std::endl;
     RsaHelpers::getInstance().encryptRsa("123123", RsaHelpers::PERSON2);

/*
    if (i>0)
    SecretKey::calculateKey(i,10,10,10);
    else
    SecretKey::calculateKey(17,50,50,50);
*/
    //ScramblerEndpoint scrambler(addr, schemasdir);
    //scrambler.init(thr);
    //scrambler.start();
    //scrambler.shutdown();
}
