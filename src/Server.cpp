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
#include <MessageBusinessLogic.hpp>
#include <RandomHelpers.hpp>
#include <functional>
#include <random>

void drawHeaderMessage(int threads)
{
    std::cout << "**************************" << std::endl;
    std::cout << "**** Cripto Method   *****" << std::endl;
    std::cout << "**************************" << std::endl;
}

int main(int argc, char * argv[])
{
    std::cout << std::endl << "GERANDO OS DADOS DO PROTOCOLO, DA PERSONA 01 PARA PERSONA 02"
                           << std::endl;

    std::mt19937::result_type seed = time(0);
    auto dice_rand = std::bind(std::uniform_int_distribution<int>(6,12),
                               std::mt19937(seed));

    std::string lixoTerminator = RandomHelpers::getInstance().getRandomWord(dice_rand());

    SecretValueProtocol protoFrom1 = SecretValueProtocolBuilder::buildProtocol(2,3,1,lixoTerminator,13);
    protoFrom1.dump();

    std::string encryptedProto = SecretValue::encryptSecretValue(protoFrom1,
                                                                 RsaHelpers::PERSON1,
                                                                 RsaHelpers::PERSON2);

    std::cout << std::endl << "DADOS GERADOS PARA PERSONA 01" << std::endl << std::endl
              << encryptedProto << std::endl << std::endl
              << "ENVIANDO PARA PERSONA 2" << std::endl << std::endl;

    const SecretValueProtocol leituraProtoPor2 = SecretValue::decodeSecretValue(encryptedProto,
                                                                                RsaHelpers::PERSON1,
                                                                                RsaHelpers::PERSON2);

    std::cout << "--------------------------------------"  << std::endl
              << "DADO RECEBIDO COM SUCESSO POR PERSONA 2" << std::endl
              << "---------------------------------------" << std::endl;

    leituraProtoPor2.dump();

    std::cout << "GERANDO OS DADOS DO PROTOCOLO, DA PERSONA 02 PARA PERSONA 01"
              << std::endl;

    std::string encryptedProto2 = SecretValue::encryptSecretValue(protoFrom1,
                                                                 RsaHelpers::PERSON2,
                                                                 RsaHelpers::PERSON1);

    std::cout << std::endl << "DADOS GERADOS PARA PERSONA 02" << std::endl << std::endl
              << encryptedProto2 << std::endl << std::endl
              << "ENVIANDO PARA PERSONA 1" << std::endl << std::endl;

    const SecretValueProtocol leituraProtoPor1 = SecretValue::decodeSecretValue(encryptedProto2,
                                                                                RsaHelpers::PERSON2,
                                                                                RsaHelpers::PERSON1);

    std::cout << "---------------------------------------" << std::endl
              << "DADO RECEBIDO COM SUCESSO POR PERSONA 1" << std::endl
              << "MESSAGEM SERA ENVIADA PARA PERSONA 2   " << std::endl
              << "---------------------------------------" << std::endl;

    leituraProtoPor1.dump();

    std::cout << "---------------------------------------" << std::endl
              << "PERSONA 1 PROTEGE A MENSAGEM:          " << std::endl
              << "---------------------------------------" << std::endl;

    std::string message("ITA POS GRADUAÇÃO 2019 - DISCIPLINA CT208 - 1o. BIMESTRE.");

    MessageBusinessLogic::encryptMessage(message, protoFrom1); // Usando protocolo de 1 ...

    std::cout << "---------------------------------------" << std::endl
              << "PERSONA 1 ENVIA:                       " << std::endl
              << "---------------------------------------" << std::endl
              << message << std::endl << std::endl;

   std::cout << "---------------------------------------" << std::endl
              << "PERSONA 2 INICIA DECRYPTO!            " << std::endl
              << "--------------------------------------" << std::endl;

    MessageBusinessLogic::decryptMessage(message, leituraProtoPor2); //Usando Protocolo de 2....

   std::cout  << "--------------------------------------"  << std::endl
              << "PERSONA 2 E A MENSAGEM É ..           "  << std::endl
              << "--------------------------------------"  << std::endl
              << message << std::endl << std::endl;

    std::cout << "FIM.";
}
