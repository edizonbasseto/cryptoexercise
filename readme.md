# CT208 - Exercicio 1o Bimestre - Método Criptográfico

*Esse programa é um exercicio entregue no primeiro bimestre de 2019, na disciplina CT208,
professor Dr. Nei Soma, do programa de pós graduação em Eng. Eletrônica e Computação - PG/EEC  - ITA.*

O exercício propõe a criação de um método capaz de criptografar

## Como baixar

```git
git clone --recurse-submodules -j8 <https://github.com/edizonbasseto/cryptoexercise.git>
```

## Como compilar

Desenvolvido em C++, testado somente em ambiente Linux, para compilar é necessário:

- Pacote Build Essentials
- CMake

Para o pacote NIST, é necessário:

- gsl
- texlive-core

Passos:

  1. Baixe o código fonte, conforme indicado em [como baixar](#Como-baixar).
  2. BOOST não fornece métodos para CMAKE, por isso:
       1. cd 3pp/boost
       2. ./bootstrap.sh
       3. ./b2 header
       4. cd ../../
  3. Crie uma diretório build, dentro do novo diretório baixado.
  4. Execute:
       1. cd build
       2. cmake ../
       3. make install (may require privileges).
  5. O diretório ../dist será criado com o executável.

## Arquitetura

### Premissas

1. Não é escopo desse trabalho a preocupação com execuçõs multi-threads.
2. Não é escopo desse trabalho multi-plataformas.

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
