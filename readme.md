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
- boost

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
3. O sistema não é um sistema validado e "production-ready".
4. Não otimizado para performance.

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
sigilo. O lixo tem um tamanho aleatório entre 16 e 48 caracteres, além, dos terminadores. Para geração do tamanho de forma
aleatória, não houve preocupação de usar um gerador criptográfico. O lixo é composto de parte esquerda e parte direita.
Por ventura, uma combinação de terminadores pode se coincidir com a chave gerada, ou, até mesmo com próprio lixo aleatório gerado.
Para evitar essa sitação, recomenda-se que o terminador tenha pelo menos tres caracteres diferentes.
No exemplo que está sendo apresentado, aproveitando-se da randomicidade do gerador randomico utilizado, está sendo gerado um terminador que não se repete e tem tamanho randomico entre 6 e 12.


### O Protocolo

O protocolo da chave secreta tem como divisor de informações um ponto e virgula, e contem as seguintes informações, não necessariamente neste ordem:

     1. O Número Gerador: número responsável pela dízima de fração continuada.
     2. O ponto de inicio: posição, à partir do primeiro número da dízima, que irá iniciar a geração da chave secreta.
     3. Pulo: a quantidade de posições que deve-se pular, para ler o próximo número da dízima e continuar a formar a chave secreta.
     4. Delimitador de Lixo: o conjunto de caracteres na quantidade de repetições indicada, que determina que a palavra lida é, na verdade, uma palavra aleatória qualquer.
     5. Repetições do delimitardor de lixo: a quantidade que o caracter precisar ser repetido para ser considerado um lixo.
     6. Checksum: um DIGEST SHA256, com todo conteúdo da palavra secreta.

### RSA

O envio da palavra secreta entre as partes se dá por meio de uma criptografia RSA, com uma chanve de 4096 bits. Isso permite o envio de uma palavra secreta maior, e com maior proteção.
A biblioteca CryptoPP utiliza o método (OAEP) Optimal Asymmetric Encryption Padding, para geração da mensagem criptograda.
Como esse trabalho é meramente para fins acadêmicos, as chaves estão fixadas no código, tanto a privada quando as publicas.

### A Confirmação de chaves entre as partes

Para que ocorra uma transação segura, no cenário de duas pessoas trocando mensages, primeiro PERSONA 01 envia a palavra secreta para PERSONA 02.

PERSONA 02 recebe a palavra, utilizando de sua chave privada, descriptografa o valor e valida o sender o checksum.

PERSONA 02 faz o processo reverso, usando a chave publica de PERSONA 01.

PERSONA 01 valida a chave, o emissor e o checksum, além de verificar o conteúdo conhecido.

Nesse momento, PERSONA 01, retorna a mensagem criptografada para PERSONA 02.

PERSONA 02, em posse do protocolo, poderá descriptografar a mensage.

### A Mensagem enviada

A mensagem enviada entre A e B, após confimação conforme descrito, ira conter [LIXO ESQUERDO] [MENSAGEM CIFRADA] [LIXO DIREITO].
A mensagem cifrada, além de embaralhada com a chave secreta criada, irá estar em BASE64. Essa escolha foi feita sem fins criptograficos, mas é a maneira mais segura de se transportar um trem de bytes sem o surgimento de caracteres não imprimiveis.

## RESULTADO EXEMPLO

```log
GERANDO OS DADOS DO PROTOCOLO, DA PERSONA 01 PARA PERSONA 02
------------------------------------------------
SECRET VALUES PROTOCOL
------------------------------------------------
Start Position:2
Jump: 3
GarbageTerminatorSize: 1
GarbageTerminator: 8F71A92CD3
NumberGenerator: 13
------------------------------------------------
Checksum Gerado....0BFF8ADAF2525F6A99E37415D6339EA7FF7A547EEFDE5E681FF99F5A4A39E8EB
DADOS GERADOS PARA PERSONA 01

3F46399D7E33D893C2C4CF08F35B60396435C35D3AA90F2AC9684EF3E51BD022BBE65D377A6BDF74CB4A6FBDD77B2E421F1445158220CE130CED6B7EC10B256A5F8B0DDD251ACE18CCA7FECBB1A0EA3268CA25DEEFDD3609DB5370A622D9566FC3FBC2BA61162F1A28C51E2D6D86FFE00C36A805DFCCD76072F6F2F0E434FB835F5328C459E9224649A50193532528B89BA3946AFF0FB97782A9A2B278B0FA8CEB1ECCC77191CD45CA37A25F78E314ACCE0458E3598767E555B2750329A05BDFF7CEA36513B37DB2C5FCF495B24922CE525F8293847664BD8911D64FC9FF531BBA6B9C5CC7B3C4A851F20E721C2D865B47E621EFB3F38405076D5EAE2D3EF1C8928F034B52EF05DDAB8580CCC552FB43C2ECD19B8DE59C41B80598BA85DE14CEC54D7B5C643B40ED198A959B705A22681C6B2BD071EDF1584BD702568E695CF8D444A36BA9263805C5BD1B367BC154846C5E2C6ADE9239407C549A4AD1FCBBE7E0E499F51BFFF0DB56DD96B92D765A7DEEBE106F268E97B18D1752F6EA1C7E9120B3F12F00A8A098AA9FA1E3BEE884E9821999E1291670DC25EB3388C0453ADAEAFF2BCC5EE0D6C9E71907B27281B97D41F936FC1A690559D63C20181186BCD68A454FEA8D72498029AB0600F16EAA0397611FF3B919292C5EF9CD169C265D1C443E4655D1E787B3EBA20CC1BA3F148E4C679B514F60343D3070E8BBF1051ECB

ENVIANDO PARA PERSONA 2

2;3;1;8F71A92CD3;13;0;0BFF8ADAF2525F6A99E37415D6339EA7FF7A547EEFDE5E681FF99F5A4A39E8EB
Validando payload recebido...

2;3;1;8F71A92CD3;13;0
Dado validado pela pessoa 1
--------------------------------------
DADO RECEBIDO COM SUCESSO POR PERSONA 2
---------------------------------------
------------------------------------------------
SECRET VALUES PROTOCOL
------------------------------------------------
Start Position:2
Jump: 3
GarbageTerminatorSize: 1
GarbageTerminator: 8F71A92CD3
NumberGenerator: 13
------------------------------------------------
GERANDO OS DADOS DO PROTOCOLO, DA PERSONA 02 PARA PERSONA 01
Checksum Gerado....2DF30B67E4284179479F27ABBABDE1AE9D3C052396AF36D1F964BC032490D7A0
DADOS GERADOS PARA PERSONA 02

2C8A4CA647FB32DA408761DC5D002836C5AB8BE236EDDCE66830215A6371FF57E5D11D66052488CE592D9FBF06533D113278B91F6E6615A74607ECAA64D26D42D933CBE965C995336E96DD4420DFEA20B144BFAA738589BC5C79C3D2591C8D920B6F8549A9AACD0CAF701517BC914DCA2D96909F7ACB6F75BBDA8F32D3434135AF65F2E6E6D416FB188FC46C9A0F7578D0B40C936C1947CC7A471EC62824C68EBF07381983B429E19284F8CBA40D1F520EDC41230D00E55BA45F91991F9D87FDD4178F115D3F36616F96568BA4CBC94DBF0AB3A324D0FCB9495DB6884D48703F72BB61FD3FC088BB50CA33817590B9C5A21E36D57E53DE0444BF1F0787F5FC7B4D684E08C6C78965F87EDA6D718703B9182FD2EAA725290B3EFBE6237D9B1512C48D2F31BD3D9EE7476627F0E48512579953BD1123F47D6449BAF5465A143627A2A4D717EA5A9282B8D54335890D6E2F5CAA9CCF94A6E092263E54B01FB902548312AC56A733EDC09CD905632C674EA39497E99D01F99B561DE219C4DC246D5B5B491A10908D495CBB2E801C208DB6E14C736CE3C9952A3EDFFB26259E79DD6EF1FA5DE0BAF9C452EB17E80F4E6358EA9AB19AB7873327A388479D8E5D11F56CC279ED872CCECBDEDAB7FB7DDA6B7090C35618C076575E62D781B30225C6A389AD6B40C7AD0AC7370C052881A7D899BDB6A32A4EB13018FB876634AD709A651F

ENVIANDO PARA PERSONA 1

2;3;1;8F71A92CD3;13;1;2DF30B67E4284179479F27ABBABDE1AE9D3C052396AF36D1F964BC032490D7A0
Validando payload recebido...

2;3;1;8F71A92CD3;13;1
Dado validado pela pessoa 0
---------------------------------------
DADO RECEBIDO COM SUCESSO POR PERSONA 1
MESSAGEM SERA ENVIADA PARA PERSONA 2
---------------------------------------
------------------------------------------------
SECRET VALUES PROTOCOL
------------------------------------------------
Start Position:2
Jump: 3
GarbageTerminatorSize: 1
GarbageTerminator: 8F71A92CD3
NumberGenerator: 13
------------------------------------------------
---------------------------------------
PERSONA 1 PROTEGE A MENSAGEM:
---------------------------------------
**** CALCULO DA CHAVE *****
Fração Continua - Representação LINEAR!
3 1 1 1 1 6
-------------
Full Calculated number: 3.605551275463989293119221267470495946251296573845246212710453056227166948293010445204619082018490717673514182024063540376030678264697807705163017166892709757742690564274152633233830394962346944796273229996288003268856427213072112733
Tithe                 : 605551275463989293119221267470495946251296573845246212710453056227166948293010445204619082018490717673514182024063540376030678264697807705163017166892709757742690564274152633233830394962346944796273229996288003268856427213072112733
Selected numbers      : 05768912679459744115526491401819171826473769006169054967533

 -Tamanho do Lixo Esquerdo: 85
 -Tamanho do Lixo Direito: 89

Embaralhando os dados.
 Chave     : 0011001100110011001101010011011100110110001110010011010000110101001100000011100100110110001100010011011000110000001100000011100100110110001101110011001100110111001101000011011000110010001110000011000100110111001100010011100100110001001110000011000100110000001101000011000100111001001101000011011000110010001101010011010100110001001100010011010000110100001101110011100100110101001101000011100100110111001101100011001000110001001110010011100000110110001101110011010100110000 Tamanho original da chave   : 59
 Mensagem  : 0010111001000101010100100101010001010011010001010100110101001001010000100010000000101110011011110011000100100000001011010010000000111000001100000011001001010100010000110010000001000001010011100100100101001100010100000100100101000011010100110100100101000100001000000010110100100000001110010011000100110000001100100010000001001111100000111100001110000111110000110100000101010101010001000100000101010010010001110010000001010011010011110101000000100000010000010101010001001001 Tamanho original da mensagem: 59
 Novo Valor: 0001110101110110011001110110001101100101011111000111100101111100011100100001100100011000010111100000011100010000000111010001100100001110000001110000000101100011011101110001011001110011011101100111100001111011011000010111000001110010011010110111100001110100000101000001110000011001000011010000011100000010000001110001010101111110101100101111011110110011111101000111100001100000011100000111100001100101011100010001001001100010011101100110100000010110011101100110000101111001
 Mensagem embaralhada (STR): eWF2Fmh2YhJxZXhwYHj0s/eyfhUHAgcNGRwUdHhrcnBhe3h2cxZ3YwEHDhkdEAdeGBlyfHl8ZWNndh0=
---------------------------------------
PERSONA 1 ENVIA:
---------------------------------------
616FFD8A758A03301B8FBEFEE9DEFF075D5B36F1B80777D67E72EE6E4FCAE6D89744C5893DC9AD98EE97E8F71A92CD3eWF2Fmh2YhJxZXhwYHj0s/eyfhUHAgcNGRwUdHhrcnBhe3h2cxZ3YwEHDhkdEAdeGBlyfHl8ZWNndh0=8F71A92CD3DC4834EDE6F8214325CE1EDCDA91BA33366B12D397FDBABB2319D4FB74F0115E6943E58325BD3128157D30721

---------------------------------------
PERSONA 2 INICIA DECRYPTO!
--------------------------------------
Lixo removido da mensagem.
 - Terminator procurado       : 8F71A92CD3
 - Lixo Esquerdo encontrado em: 95
 - Lixo Direito encontrado em : 80
 - Mensagem limpa             : eWF2Fmh2YhJxZXhwYHj0s/eyfhUHAgcNGRwUdHhrcnBhe3h2cxZ3YwEHDhkdEAdeGBlyfHl8ZWNndh0=
A mensagem recebida foi:
 Tamanho: 59
 > yavhvbqexp`x����~
txkrpa{xvswc^r|y|ecgv

**** CALCULO DA CHAVE *****
Fração Continua - Representação LINEAR!
3 1 1 1 1 6
-------------
Full Calculated number: 3.605551275463989293119221267470495946251296573845246212710453056227166948293010445204619082018490717673514182024063540376030678264697807705163017166892709757742690564274152633233830394962346944796273229996288003268856427213072112733
Tithe                 : 605551275463989293119221267470495946251296573845246212710453056227166948293010445204619082018490717673514182024063540376030678264697807705163017166892709757742690564274152633233830394962346944796273229996288003268856427213072112733
Selected numbers      : 05768912679459744115526491401819171826473769006169054967533
Embaralhando os dados.
 Chave     : 0011001100110011001101010011011100110110001110010011010000110101001100000011100100110110001100010011011000110000001100000011100100110110001101110011001100110111001101000011011000110010001110000011000100110111001100010011100100110001001110000011000100110000001101000011000100111001001101000011011000110010001101010011010100110001001100010011010000110100001101110011100100110101001101000011100100110111001101100011001000110001001110010011100000110110001101110011010100110000 Tamanho original da chave   : 59
 Mensagem  : 0001110101110110011001110110001101100101011111000111100101111100011100100001100100011000010111100000011100010000000111010001100100001110000001110000000101100011011101110001011001110011011101100111100001111011011000010111000001110010011010110111100001110100000101000001110000011001000011010000011100000010000001110001010101111110101100101111011110110011111101000111100001100000011100000111100001100101011100010001001001100010011101100110100000010110011101100110000101111001 Tamanho original da mensagem: 59
 Novo Valor: 0010111001000101010100100101010001010011010001010100110101001001010000100010000000101110011011110011000100100000001011010010000000111000001100000011001001010100010000110010000001000001010011100100100101001100010100000100100101000011010100110100100101000100001000000010110100100000001110010011000100110000001100100010000001001111100000111100001110000111110000110100000101010101010001000100000101010010010001110010000001010011010011110101000000100000010000010101010001001001
 Mensagem embaralhada (STR): SVRBIFBPUyBHUkFEVUHDh8ODTyAyMDE5IC0gRElTQ0lQTElOQSBDVDIwOCAtIDFvLiBCSU1FU1RSRS4=
Decrypt concluído.

--------------------------------------
PERSONA 2 E A MENSAGEM É ..
--------------------------------------
ITA POS GRADUAÇÃO 2019 - DISCIPLINA CT208 - 1o. BIMESTRE.

FIM.
```
