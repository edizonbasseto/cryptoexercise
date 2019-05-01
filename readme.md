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

Passos:

  1. Baixe o código fonte, conforme indicado em [como baixar](#Como-baixar).
  2. Crie uma diretório build, dentro do novo diretório baixado.
  3. Execute:
       1. cd build
       2. cmake ../
       3. make install
  4. O diretório ../dist será criado com o executável.

## Arquitetura

### Geração de número randômicos
