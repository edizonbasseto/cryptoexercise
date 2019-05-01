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
    std::vector<unsigned long> vec;

    if (i>0)
    vec = SecretKey::calculateKey(i,0,0,0);
    else
    vec = SecretKey::calculateKey(17,0,0,0);



  std::ostringstream oss;

  if (!vec.empty())
  {
    // Convert all but the last element to avoid a trailing ","
    std::copy(vec.begin(), vec.end()-1,
        std::ostream_iterator<int>(oss, ","));

    // Now add the last element with no delimiter
    oss << vec.back();
  }
   std::cout << oss.str() << std::endl;
    //ScramblerEndpoint scrambler(addr, schemasdir);
    //scrambler.init(thr);
    //scrambler.start();
    //scrambler.shutdown();
}
