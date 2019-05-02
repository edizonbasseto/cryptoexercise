# CT208 - Exercicio 1o Bimestre - Método Criptográfico

*Esse programa é um exercicio entregue no primeiro bimestre de 2019, na disciplina CT208,
professor Dr. Nei Soma, do programa de pós graduação em Eng. Eletrônica e Computação - PG/EEC  - ITA.*

O exercício propõe a criação de um método capaz de criptografar um dado baseado em uma chave
criada através do método da raiz quadrada com fração continuada. A configuração da distribuição dos resultados
das frações continuadas é normal, gerando assim a mesma probabilidade de surgimento de escolha de um número,
desde que desconsiderado o último elemento.

O número utilizado para geração da fração continua será chamado de numero gerador, e, junto com um protocolo
que será explicado neste readme, será enviado entre as partes. O conjunto de dados formado por esse protocolo será
chamado de palavra secreta.

Para facilitar a comunicação entre as partes, o sistema irá prover uma REST API, encapsulando as lógicas de negócio da aplicação.
**Sistema meramente acadêmico, sem utilização para ambientes produtivos**

## Como baixar

```git
git clone --recurse-submodules -j8 <https://github.com/edizonbasseto/cryptoexercise.git>
```

## Como compilar

Desenvolvido em C++, testado somente em ambiente Linux, para compilar é necessário:

- Pacote Build Essentials
- CMake
- libgmp3-dev

Passos:

  1. Baixe o código fonte, conforme indicado em [como baixar](#Como-baixar).
  2. Crie uma diretório build, dentro do novo diretório baixado.
  3. Execute:
       1. cd build
       2. cmake ../
       3. make install (may require privileges).
  4. O diretório ../dist será criado com o executável.

## Desenvolvimento

### Premissas

1. Não é escopo desse trabalho a preocupação com execuçõs multi-threads.
2. Não é escopo desse trabalho multi-plataformas.
3. Não é escopo deste trabalho proteger as rotas de comunicação REST criadas com intuito de facilitar a demonstração.
4. O sistema não é um sistema validado e "production-ready".

### Geração de número randômicos

A geração dos números randomicos, foi decidido utilizar o método Hash_DRBG da biblioteca Random Number Generator, contido no pacote Crypto CPP. <https://www.cryptopp.com/wiki/RandomNumberGenerator>.

As seguintes carecteristicas fizeram desse método uma boa escolha:

1. Deterministic Random Bit Generators (DRBG) é uma especificação NIST, de 2015, para geração valores aleatórios para aplicativos criptográficos <https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-90Ar1.pdf>.

2. Entropy: ao gerar dados, a biblioteca garante utilizar (no Linux) /dev/urandom (blocking=false), que está em acordo com a norma RFC PATCH v12 <https://lkml.org/lkml/2017/7/20/993>. Especificamente para o método Hash_DRGB, somente 3 métodos da CryptoCPP possuem conformidade com as normas: NIST.SP.800-90Ar1. São eles: NonblockingRng, RdRand e RdSeed. NonblockingRng irá confiar no sistema operacional, enquanto RdRand e RdSeed são dependentes do hardware(AMD ou Intel) de execução. Para manter compatilibade com VMs, foi escolhido o NonblockingRng.

3. Seeding: A utilização de um SEED aleatório somado ao uso do /dev/urandom, certifica que o dado gerado será imprevisível. A semeadura de dados é feita de forma automática no Pool.

4. SHA: ao finalizar a palavra randomica, o método utiliza o algoritmo SHA-256 para gerar o stream a partir do pool gerado (passos 1 e 2) e retornar a palavra randômica de tamanho desejado. <https://www.cryptopp.com/wiki/NIST_DRBGs#Randomness_Source>

### Teste de valores randomicos

Como a escolha feita de gerador de número randomico gera como resultado um valor criptografico SHA-256, o teste do gerador não pode utilizar o set de testes recomendado: DieHard.

Para tal finalidade, o set de test NIST é mais adequado. <https://csrc.nist.gov/projects/random-bit-generation/documentation-and-software>.

A CryptoPP fornece uma ferramenta para teste de seu gerador. Para validar, execute:

```bash
export TMPDIR=/tmp (ou outra qualquer)
cd 3pp\cryptopp
./cryptoTest.sh (aguarde)
./cryptoTest -v 77
```

### Terminologia dos segredos

#### Mensagem

Texto original que deverá ser criptografado e descriptografado.

#### Chave Secreta

A chave secreta é composta de números gerados do cálculo das dizimas de uma raiz quadrada com fração contínua.
Será utilizada junto com a lógica XOR para criptografar ou descriptografar os dados enviados da mensagem.
A fração continua será calculada pela biblioteca GMP: <https://gmplib.org/manual/Square-Root-Algorithm.html>.

#### Palavra Secreta

É a palavra resultante do procotolo que contem todos os dados necessários para que uma mensagem seja criptografada
e descriptografada de forma correta. A palavra secreta será enviada entre as partes.

#### Protoclo da palavra secreta

Estrutura que define as regras pelas quais a mensagem foi criptografada originalmente.

#### Lixo

Quantidade de dados aleatórios anexados no antes e depois da mensagem original, afim de dificultar a quebra do
sigilo.

### O Protocolo

O protocolo da chave secreta contem as seguintes informações:

     1. O Número Gerador: número responsável pela dízima de fração continuada.
     2. O ponto de inicio: posição, à partir do primeiro número da dízima, que irá iniciar a geração da chave secreta.
     3. Pulo: a quantidade de posições que deve-se pular, para ler o próximo número da dízima e continuar a formar a chave secreta.
     4.