/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: server.cpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */

#include <BaseInclude.hpp>
#include <KeyBusinessLogic.hpp>

void drawHeaderMessage(int threads)
{
    std::cout << "**************************" << std::endl;
    std::cout << "**** Cripto Method   *****" << std::endl;
    std::cout << "**************************" << std::endl;
}

int main(int argc, char * argv[])
{
    std::cout << std::endl << "GERANDO OS DADOS DO PROTOCOLO, DA PERSONA 01 PARA PERSONA 01"
                           << std::endl << std::endl;

    SecretValueProtocol proto = SecretValueProtocolBuilder::buildProtocol(2,3,10,'A',13, 36);
    proto.dump();

    std::string encryptedProto = SecretValue::encryptSecretValue(proto,
                                                                 RsaHelpers::PERSON1,
                                                                 RsaHelpers::PERSON2);

    std::cout << std::endl << "DADOS GERADOS PARA PERSONA 01" << std::endl << std::endl
              << encryptedProto;

}
