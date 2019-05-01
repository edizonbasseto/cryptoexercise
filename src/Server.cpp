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

    std::string schemasdir("");
    //if (argc > 1)
    //{
    //    schemasdir = std::string (argv[1]);
    //}

    //ScramblerEndpoint scrambler(addr, schemasdir);
    //scrambler.init(thr);
    //scrambler.start();
    //scrambler.shutdown();
}
