/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: RsaHelper.hpp
 * @Date: Wednesday, 1st May 2019
 * @author: Edizon Basseto Jr (edizon.basseto@wiboo.com.br>)
 */

#ifndef __RSA_HELPERS__
#define __RSA_HELPERS__

#include <BaseInclude.hpp>
#include <rsa.h>
#include <osrng.h>

/**
 * Help with RSA Operations.
 */
class RsaHelpers
{
public:
    RsaHelpers(RsaHelpers const&) = delete;
    void operator=(RsaHelpers const&) = delete;

    enum Person {
        PERSON1 = 0,
        PERSON2,
        PERSON_SIZE
    };

    // Singleton.
    static RsaHelpers& getInstance()
    {
        static RsaHelpers instance;
        instance.RSA_PRIVATE_KEY[PERSON1] = "-----BEGIN RSA PRIVATE KEY-----"
                                            "MIIJKgIBAAKCAgEAzojOzaUi5kUomcE2ALUYZj/JEhhuKQ8is+h3dLhSUSrsr+bu"
                                            "GjTisB07834ZHUbbIniY9zbsSTzFwrRd5p2IkXZWxu+om4f1Zfoo8vStrM9oqOGI"
                                            "10U6GAgXzo+i6pqh2dnCVs+QP1b7WWEfveRvdy0ULlPJrJq6PEW+dFjKVtuWvjRj"
                                            "WEDdjnC8Q3iqlMxj3aB5oHq+GMHjqonWgwKLCP+hCjLvRx7jVuoS4stvcUZzdtFb"
                                            "YV6s5FBm6WPEONA+VQCk2taKFsrs1Jr5WVnqZElXxSBLBdDh/AvC83L528/qQIa5"
                                            "c6ZaLJ6+F2Z5dZLwTqbx4UuwComCt5CgL9/h7x3rxX4uiHHB3MO+ntnj9S+bbwxa"
                                            "k5BFE6xqIfCBF1bPQH9R02W1YjCuTWGyY8fbCoBE11ijkwYE6wluIDJNbFDZ0Ban"
                                            "S35Gj/CLKB2hP1z3hp3K9pKy308qsqXsHaoP9k12Armc5E3vugQCfw0lnk6nhPBy"
                                            "Q8X/M4WgTdJgnJhH2XrEJCOyiAbWgP3XBDxERXm0mING4EEGDB9GiPIVddaKWzM3"
                                            "VndNLJhCloRWezXwfFIGHxNsfXkXfHU/Qf2BlKvvo24BXIwdkzdl6ATXWyKW4N4x"
                                            "Zwg/G0WKLvlfdgJVJ9spo+KFjq9xX/BhD4Fkg20YEfIooSfiVnDTdyFkr5sCAwEA"
                                            "AQKCAgBLv1k5ius10P+HBJmtwL1mIta30EX2wRpVKVlGcaOfKUMNcIC7E9JgDRjD"
                                            "wOetGSOdjOVtJbObWLKfKk+WGQjRcLl61MLd6AtUj18dXCemTZtw9OafLUCVN8Kj"
                                            "e4Kg0H2zzG2+MPoSgPBGY5ykpHdNGjdgllJM/6J2II4tVbNAD+FFeSlGYOPhLe+e"
                                            "P08wq5Wk3wo8lUfLBLFfBpaqDfC4KCkD+JJRXz65zbeHfl0tCk2msjn1iCeYxPQ5"
                                            "fOGmhJmXy1iq+ixDF8GsZ/ozjwqsJUoPfjyFsYpwSlABwZVpzON5LvAtPkGsQ7ws"
                                            "EOVS/cUs04W6v2udMbnDYUOey1mtFEMtHT/tqL/UqeCm7+Ad3AioFcwsRdR+deTq"
                                            "FamjiiXujqew28XHoFj6l7yhYNMSyTmLWDQeTbbxtlBJJAH5OOJkt08w1WeXZbox"
                                            "sQS/7z/ZLckxYdspIP1PSvqjyoT9HbE3dWdd5zMCwR6xqhzc+qi3PvGHEGDyBmEK"
                                            "2SfMQvBLZUoDCxIFrkIlD6hH66oMchtnA486sYjmtay324Lwmyo6LIS3GAwfAop1"
                                            "NeuUoCmq76WGaHQaE2SQR4FqfBC8nQVUzj5pU2hzarMxx7SqRIieouzxW/+NX4pX"
                                            "Fd/SUhnImYNZ2TrB7lbsT2DDjXHqsRS9oeCmL8tH1eF8qXrioQKCAQEA8jiy/VYK"
                                            "p/m5ViA/4c/GQE5BywBKG32Sz14QLOFgQe1HCwO1RzFK5A1Kl5zYazKFq62ng7nH"
                                            "O1m3X1sqRew21LJQxr9s8fnDqV/LsfguPfJq9KN8T8dFRDWW7Kf76MwxmYlNB3N3"
                                            "7xk0rKbu8bBtpttQ1gzUDPpkV3opxtsxCh71jfwcRGRd9YZRiUNV+viTRJcER+JJ"
                                            "5YgUZmDakSahuM6Nd/GjEO3CmpMHWCkqRIMswF4pA6XSIW+NKAE2ZnO7U2quTQfU"
                                            "pOukq4mcxBfHnqKls4hT1PQ5y7QnhHPmaz5qrH9+BQks77VL6AaooM036lR9g4dF"
                                            "Wl+CIsNKOhq81wKCAQEA2khsQ0YI4QbrePrEh0bctbflOwCLINf8z+O5jIqdLm2/"
                                            "H/hn9Jv/YGPjIL8XbKEnGebZEufv/Ag1siW2L75+8b30Bot2YMFkp29GqK8mH9Tr"
                                            "daoxFHo/IH0M+uV7SylbyUlQ3rG3iXk+G6fgni3BQRthu/rzYzd7IdjC2D3q6I6O"
                                            "6mFwlA64hz1R0Q2dQdQb5z1Dd91taHKXEl58fQVdO2XGPy6oJQdHaWmbsZm2jatk"
                                            "g/nHecmf4zy1BTnDiHMbyZD+oj1m0vCXea8WWh0ReqLIke8cZH0uFdm1JVmPJMjV"
                                            "FwVIMmL/4PSrSmA/9RwhAQCD9aghuwF9xC/Ccz5m3QKCAQEAs5jo1kCC3DOkgUCe"
                                            "PT+CvtGHpQ5M5H9CaLFVCwH9DkTx5S/VrLjWz6svQKVSLoGibT3wNBJ+r/oAphqB"
                                            "iKDxstmYXRU4oV5Q/ngCH65mExZ4yXWiycB2EnItusF/XghxSmdsjvbF2an1zYJl"
                                            "Lx1i4FJDaMLQQ+MwnU/+Q+zoOpnj9mgVSXyl0lPKhx0/VjwTbcsPqIEXy7IPdi2g"
                                            "QfnD9bRpXqLzBq1UGqqjynGTXoNoniXzATplSNdecWgcvvBW2C4EmScSO0phqbL6"
                                            "YsdDAtOUSz7s8bw4Ulr85g/NrHz2OXq6pN89y2rAooS1aa1gJUaKXgjhmnWwlzf4"
                                            "BIcotwKCAQEAuas6s2ph6Q6awngDLNHgsI0wZaSLsy8k8qvQSzQoiLJ/DLGdsxnx"
                                            "+kpciqEgSp01Bjou0H8KyYUuL08WjbvqfLPHWr3Lvnchp63mG1uIATF56scOIk3t"
                                            "XjQgE1WZLxCJ60f6isH9zOidJKcCT2m55ShmVKAb4Hvzt5GKAqeAJboE5GZnfPic"
                                            "iyRkcH61EaZa6bFZrx5gjqRRziUinLEwYXKrU1jbW0u6uXZEIagO+Kgdwoh23Sfc"
                                            "YUxk6YH9yRWoQCaeAOBbkvdk0PNV/uaU1IycME2ECBHWXm2lQJTSRkaxwngSthEx"
                                            "d2aGQKhoHpSDmjeXByCxOEEHehXpv18H3QKCAQEA2scteLJ2+TtMdfcUA/eHJfZW"
                                            "c7yD/XfNW83VgatbNKa1cS855dERCGLFOXj/AsLnR/yBbthUO5O5A9LNmQvAbrh9"
                                            "5Fn/hUlZT9Gegxjt4KpfBZ6+SfN6bLT7dzHNvrUs1tiaIIB4j385bv/EGSjxwSzF"
                                            "KxEHXyzr3Zw7xWUYQjolCXey49PtNaMHR8AM7SUEhdPYf5oxZgm2QkAT6c8+tJS7"
                                            "aZaFTS8lA167j22lbTAPeKd4G5HtA87Wm/N5czHF2srHfGXg4XtCNMdY/L5ZCwFA"
                                            "e6lyCLUC4SoivU/2bUUbL2ZraenCFQ456pPUiQFFmi/PHT9DOAznU21lQiiO9w=="
                                            "-----END RSA PRIVATE KEY-----";

        instance.RSA_PUBLIC_KEY[PERSON1] =  "-----BEGIN PUBLIC KEY-----"
                                            "MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAzojOzaUi5kUomcE2ALUY"
                                            "Zj/JEhhuKQ8is+h3dLhSUSrsr+buGjTisB07834ZHUbbIniY9zbsSTzFwrRd5p2I"
                                            "kXZWxu+om4f1Zfoo8vStrM9oqOGI10U6GAgXzo+i6pqh2dnCVs+QP1b7WWEfveRv"
                                            "dy0ULlPJrJq6PEW+dFjKVtuWvjRjWEDdjnC8Q3iqlMxj3aB5oHq+GMHjqonWgwKL"
                                            "CP+hCjLvRx7jVuoS4stvcUZzdtFbYV6s5FBm6WPEONA+VQCk2taKFsrs1Jr5WVnq"
                                            "ZElXxSBLBdDh/AvC83L528/qQIa5c6ZaLJ6+F2Z5dZLwTqbx4UuwComCt5CgL9/h"
                                            "7x3rxX4uiHHB3MO+ntnj9S+bbwxak5BFE6xqIfCBF1bPQH9R02W1YjCuTWGyY8fb"
                                            "CoBE11ijkwYE6wluIDJNbFDZ0BanS35Gj/CLKB2hP1z3hp3K9pKy308qsqXsHaoP"
                                            "9k12Armc5E3vugQCfw0lnk6nhPByQ8X/M4WgTdJgnJhH2XrEJCOyiAbWgP3XBDxE"
                                            "RXm0mING4EEGDB9GiPIVddaKWzM3VndNLJhCloRWezXwfFIGHxNsfXkXfHU/Qf2B"
                                            "lKvvo24BXIwdkzdl6ATXWyKW4N4xZwg/G0WKLvlfdgJVJ9spo+KFjq9xX/BhD4Fk"
                                            "g20YEfIooSfiVnDTdyFkr5sCAwEAAQ=="
                                            "-----END PUBLIC KEY-----";

        instance.RSA_PUBLIC_KEY[PERSON2] =  "-----BEGIN PUBLIC KEY-----"
                                            "MIICITANBgkqhkiG9w0BAQEFAAOCAg4AMIICCQKCAgBsHpuRaotsKIuUHNiWyfiJ"
                                            "ZYnYMGZlxZsi18wpdvF+Q97BUi2vR/yoPt1KnTrdtPhiwFDnH+cUSQMg/WgJpRQE"
                                            "YpCMTrzKzp9LUTTCqdT1Aoyybz0PJQy74QQzvo3v6nSA5M7aYHAytxNT+JNf7y27"
                                            "ndAWFhuO6WaATroFqDhaxdOeflU9mQI9Zn9g4jLA3F3HAMZqUfEMR8FEjpMjg0MH"
                                            "R7YNjUddNtYH0S6o2w559xVHIoaoGFF4ItVyE0uVtnZ8/7uZ/XLfMUdMDzc1j/zM"
                                            "DQ7EcwNAXtfEXmLAmuFOpqGKZgkBNgUch6uU0Zq9304N+q7+/ThCtgT5P6Hvi65u"
                                            "cXqvlNjQhjtgIi0IwyyD52yyHebDLtDTm+2sZPIRKLMUG5kzZEiYgvOeq9jUnaez"
                                            "9WRZUCIQ4snY7/2oR5buUUmJKa3CStqSUmRSihf9GtstbKTrlgfZud2uuzb11Mir"
                                            "mPBbFXXmz5c/2NofeJcFHPMVwNdi+OkjTrjVHS7AmfPfhJ2VRjgUBxt5Q44Up5zc"
                                            "qOmRvjeENSB4mVnmV7sn4o5D7mfWoXs5OXTxcNjxisMEuByh8OWZv9U9nCdbLkNd"
                                            "6KyegQRL/9BfyDQaFx1IEQTbBkwyunkhFocPuS/pnd6c32Ht0a8d9asnSCf0KsK7"
                                            "iF7UqwKYSjPPDeh3s7SN2QIDAQAB"
                                            "-----END PUBLIC KEY-----";

        instance.RSA_PRIVATE_KEY[PERSON2] = "-----BEGIN RSA PRIVATE KEY-----"
                                            "MIIJKAIBAAKCAgBsHpuRaotsKIuUHNiWyfiJZYnYMGZlxZsi18wpdvF+Q97BUi2v"
                                            "R/yoPt1KnTrdtPhiwFDnH+cUSQMg/WgJpRQEYpCMTrzKzp9LUTTCqdT1Aoyybz0P"
                                            "JQy74QQzvo3v6nSA5M7aYHAytxNT+JNf7y27ndAWFhuO6WaATroFqDhaxdOeflU9"
                                            "mQI9Zn9g4jLA3F3HAMZqUfEMR8FEjpMjg0MHR7YNjUddNtYH0S6o2w559xVHIoao"
                                            "GFF4ItVyE0uVtnZ8/7uZ/XLfMUdMDzc1j/zMDQ7EcwNAXtfEXmLAmuFOpqGKZgkB"
                                            "NgUch6uU0Zq9304N+q7+/ThCtgT5P6Hvi65ucXqvlNjQhjtgIi0IwyyD52yyHebD"
                                            "LtDTm+2sZPIRKLMUG5kzZEiYgvOeq9jUnaez9WRZUCIQ4snY7/2oR5buUUmJKa3C"
                                            "StqSUmRSihf9GtstbKTrlgfZud2uuzb11MirmPBbFXXmz5c/2NofeJcFHPMVwNdi"
                                            "+OkjTrjVHS7AmfPfhJ2VRjgUBxt5Q44Up5zcqOmRvjeENSB4mVnmV7sn4o5D7mfW"
                                            "oXs5OXTxcNjxisMEuByh8OWZv9U9nCdbLkNd6KyegQRL/9BfyDQaFx1IEQTbBkwy"
                                            "unkhFocPuS/pnd6c32Ht0a8d9asnSCf0KsK7iF7UqwKYSjPPDeh3s7SN2QIDAQAB"
                                            "AoICAGRFjqmyUlOg1rIqfoR6E9H5JXomiRDhzxrlYCckdJtRfol0GYJyFNREWR8V"
                                            "6r4rVCDhkyaG49xgSlKSMaagPoxCjSRS8ax1LC7BxVi0ARipoKrrl4kwJzsnWKpU"
                                            "k3Zpzlqr2VuWDPg76eT6qFNUkulpVs7k+fH0bGeam9MbTAiDZ9uZ9pwGB5nCMWg8"
                                            "4C0VMrOY+GsqS4/EDG30fGl3Fvbtft3apNDCRoVBbzCS2D4s9MLgNlo3E3eDdskx"
                                            "M+xJKGKNGgOalqqAHUtg4Sb/vsfPZF60+9L7IsivcI6IFWTIDRE5yCgjXWI0QODn"
                                            "88ccDlvQnfNGDKNyA/LVHO34cXAvmXdh1g3bEN4Siku7gBCB4xfapddlXWWCoQm2"
                                            "uWbffz0tMgDurYWmkMnfRSDJOFw5f2EtEZoCV+NnkKjNQSePrO+TiT3DJvNMym6D"
                                            "OLK1FsVK9Q4HUO+nC5CJViK+ukXlBsg+bhcC5/UCMy3K1k+2ypnoI8wqzlTn3+Y+"
                                            "dCA+2bWK35f28PEnku4JZoucIyYHEZw9ykLWHZJUcqe9RLW9QdCWoRLhM36t2/OG"
                                            "t/Ebv1mZQfEMdUoTeGY5n8xh1XnBoINgxMr0ajfGy47TF4g53+L/ScfOA6O8OmJ1"
                                            "HUoK+lDAm+l5RaWkCaSicomkvci0TttySIrjvxP4psIjLSgxAoIBAQCoW2b064kN"
                                            "dU4sF1iqO2ujRY+f6/Ni5iIrskjkLFSQGwpFyWP2757DbftjH1mmqXpP4VyKa/B3"
                                            "Vw0MmGg/bcUHG5ZdTP4sYoo2UONG/4yiqI89rC6YV8HueilZqdHKK/sbnABCrQ9I"
                                            "whh6837KX+3CGMYUtmQjtUk7tz1BX/6dnARNpJDjtNoc/ua07BTI15+EAxmbDzf0"
                                            "jwNWL0VIxvIPrZJrUByCkMXqR7GOjCO5bSBguptZMiAHO8aaY8sh2XSiZv8gc7cn"
                                            "JRcAAip9PR8fdf+1Z30ZUVLzDdP2q9cHyBR+eBvf4Yc+v2r2uwfm7oLFWgG5U6V4"
                                            "ydK4mFSNt4mzAoIBAQCkZ3rq+iKfCkO/oa6oZn052ALHCnReIlh7k5n9Q24mTrKh"
                                            "RHRUO/ZpdDcsJ7bZKvu5Pe85k+4HVOsPB9hgiQmuGc1Cgp/YKR+yjUNMs7L5/FvD"
                                            "RYaSTilzbjRFzxC2rDy3KiVk9jTgFDcCWZiVzXIbyEOy8ev8dsFMhUyXHBxcXdXn"
                                            "wBO0m3yHJe7Y4MCycxSiEB6ciL99EP4suKdtWXOyZbbztlMN2yLsZ57tWrQ6Oh8R"
                                            "1neLw1olOQFEWqkpVVM7rpzlLACMXHQPMaA4fH38DbuPyEqUluh41OgylmgJUwz1"
                                            "DUrfOUzhjGRW2pnIK2+XkhNhq3TDQPIs3f/lHGxDAoIBAQCIVfx6OoMyMtyrN/zF"
                                            "Xnk8LwiwKRNf852YZThCDuQsDrmy6fPZ9RJMkLQTAUBIhtZV+dpG/kItYoFewc0q"
                                            "EGqN5vlNdRwgNWxXsAldZXUuA/J7rwPMusSBqsvxoGQTpKolIZ/UXvERqpzIdIco"
                                            "u6Z+mDFQdKODhztW8HzahDJc0AtsFOiAfeRjtsh9mvD59CNpdFk4CIr3sRiyonUp"
                                            "CnLb32PDI4zy7upXXtea6EHF12lw660B/mWRdgbO4CGPt9mL6nyQeyTGvnJxv09J"
                                            "PEYH5Da/YJ8d8Y2K5pfQGjh4RL7T69Am7Svo1Hp6c9tiV6PuzYS339UQi9/pPPK8"
                                            "EPWhAoIBAFOAE1ghL1BjoEFGVzVEyLmGUvLRBoWBIDuznfSaOOnP8r4hzIuz4NVy"
                                            "p0sP6LioMi3FnSk7Txv+L1z0+RsevwHkLPJo8dKSIH1JbjMY2gBKAjlNqKnKdRch"
                                            "k/8Yyj5dgIDvMQr0Waqt2bqh0vPS4u/laS0L3nXdwxOgaGQfbPAk4K3SSq/igP8L"
                                            "byJMFNMNzB773PBYLBnTdaU1LCRH2JF1Q9TId6qD8FrtzjRzazJfrsQaj6E22SQq"
                                            "rdAP0/cgVSPs7dcf4C9qDbBh3iSSZlKMjwTaD7ckZnJogH6hEboaqmwUEkEKE1hD"
                                            "O/s5D/4wwX7UPG/Q6374D4hmQMAXDY0CggEBAIQAx8Qhu213MZMCwn7ezM1ix+yF"
                                            "NNeqhogUQj77OeoJsG/Npl9FXB2LHD65RKfo6YJ5l2XgN3Ju4CjxZq6KCFa/9bn9"
                                            "hv/ZioxRUJa2/FjPznhp/KWfhY8LnGtWcRQQjLc7A9ezvBaCbBha8bsK/OglRd/W"
                                            "51JDdqNbFSIs530ZqCaIBXoZXMkXR2dMDqzlZnZaZqFWBajBOE1cYYF7/2UOHE3K"
                                            "EWUDNIcTqWs/vhB8KAVVhaKltC826UsSWqqxVSndrGyy8pU7QXKes1aUgsXpjb5V"
                                            "V5W/2ODKWxVwbHdcJKx84IE+li3T/rgGVzWtImSGPFWe/jKiWiqO+f4RURs="
                                            "-----END RSA PRIVATE KEY-----";
        return instance;
    }

    const std::string& getPEMPrivateKey(Person p);
    const std::string& getPEMPublicKey(Person p);

    /**
     * Encrpyt data with RSA of a given person
     */
    const std::string encryptRsa(const std::string& data, Person p);

    /**
     * Decrpyt data with RSA of a given person
     */
    const std::string decryptRsa(const std::string& data, Person p);

private:
    RsaHelpers();

    /**
     * Static rando number generator needed for RSA
     */
    CryptoPP::AutoSeededRandomPool& rng_get();

    static const std::string PRV_HEADER;
    static const std::string PRV_FOOTER;
    static const std::string PUB_HEADER;
    static const std::string PUB_FOOTER;

    /**
     * Internal method to transform PEM to readble key
     */
    void getCryptoPrivateKey(CryptoPP::RSA::PrivateKey& key, Person P);

    /**
     * Internal method to transform PEM to readble key
     */
    void getCryptoPublicKey(CryptoPP::RSA::PublicKey& key, Person P);

    std::string RSA_PRIVATE_KEY[PERSON_SIZE];
    std::string RSA_PUBLIC_KEY[PERSON_SIZE];
};


#endif