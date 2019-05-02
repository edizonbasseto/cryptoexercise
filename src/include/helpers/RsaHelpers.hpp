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
    };https://www.cryptopp.com/wiki/Keys_and_Formats

    // Singleton.
    static RsaHelpers& getInstance()
    {
        static RsaHelpers instance;
        instance.RSA_PRIVATE_KEY[PERSON1] = "-----BEGIN RSA PRIVATE KEY-----                                  "
                                            "MIICWgIBAAKBgG4zWcfOqQ++cUlCJNidbN6lZtC+fEoPSCTRREk8olCH0JJTFham "
                                            "c2zIBWxZesszY+jF96UUbbaGA+58zgm+0HGpu1/TMkQJEhfioYYiZIK3vPB5HPgu "
                                            "rxaDj3f8I5/Ya+ikWFy7IBbZ5CEgEJSVpkeD/i/JurmnBGBqcgtUTeJJAgMBAAEC "
                                            "gYBVEg8cz8xy+vE5PHZ1QhHpToYwXtxTz7hBs8qjPsuOn0nDq6BBm/0+3KpTGkBQ "
                                            "3TsjVq/2H+8SGCKw2Ge13jfKe+WGR9glKyWcAks1ZhRLLg6ST8FYCppEGmliA/ss "
                                            "S6eww9t3emvC87JtAQBSc0O/8eOXaQsI71jgIt/0UWLyAQJBANX8JrjM/zWp6vok "
                                            "5t6oXHESt97/SADJSiZMNjmhD8SEreLwvYXBKiMkvGmIsf2kUPS1HRD+L4jM5dN2 "
                                            "hLSs5uUCQQCD1odn9u79c8wzQjXD7cXCFO0niX1GatMPeLWhAZcBgTx6a7GOkupJ "
                                            "qlcDYHCAQS2BBLHT7VloXkMSXgT/XpOVAkAfFJvPNb9P3RlLMfbymkOrDMv2MOAV "
                                            "dSc2/tTVdAZlRdw33T254r+rERfowDkSHT7A/Fl3cWQYG6K6HznRQFfdAkArneP6 "
                                            "X1W+AHuEUdlb0uRkS2wScohBrcHaEoN0mwQMeWc60TpTAwQEDxjugw91PxsA3j6+ "
                                            "8H1t7BGgl/5rRizpAkAJsV3rCAY5tAU49sEfqFFmoPJi0yKqC5luHtEnM/858Gnk "
                                            "p1j0B0ZFeoDIV/W++CWQw+hv8u6JBTDrYMsAaUnb                         "
                                            "-----END RSA PRIVATE KEY-----                                    ";

        instance.RSA_PUBLIC_KEY[PERSON1] = "-----BEGIN PUBLIC KEY-----                                       "
                                           "MIGeMA0GCSqGSIb3DQEBAQUAA4GMADCBiAKBgG4zWcfOqQ++cUlCJNidbN6lZtC+ "
                                           "fEoPSCTRREk8olCH0JJTFhamc2zIBWxZesszY+jF96UUbbaGA+58zgm+0HGpu1/T "
                                           "MkQJEhfioYYiZIK3vPB5HPgurxaDj3f8I5/Ya+ikWFy7IBbZ5CEgEJSVpkeD/i/J "
                                           "urmnBGBqcgtUTeJJAgMBAAE=                                         "
                                           "-----END PUBLIC KEY-----                                         ";

        instance.RSA_PUBLIC_KEY[PERSON2] = "-----BEGIN PUBLIC KEY-----                                       "
                                           "MIGeMA0GCSqGSIb3DQEBAQUAA4GMADCBiAKBgGMMHjNevdorLby4glFXcCN8m6WU "
                                           "wP88KUpJ/PuPHraDA6VWvzQRZv46YONcBl60escVps8aiWvtKfEUQ+QPTWAQ5pKj "
                                           "bwUiPBJtKRP//9GpoeOWUx8TzREl3rRRrcvRggyIcvq7M5vlgrsdT64pr0g1hPJQ "
                                           "zA+zaqS0dKHKSuavAgMBAAE=                                         "
                                           "-----END PUBLIC KEY-----                                         ";

        instance.RSA_PRIVATE_KEY[PERSON2] = "-----BEGIN RSA PRIVATE KEY-----                                 "
                                            "MIICWgIBAAKBgGMMHjNevdorLby4glFXcCN8m6WUwP88KUpJ/PuPHraDA6VWvzQR"
                                            "Zv46YONcBl60escVps8aiWvtKfEUQ+QPTWAQ5pKjbwUiPBJtKRP//9GpoeOWUx8T"
                                            "zREl3rRRrcvRggyIcvq7M5vlgrsdT64pr0g1hPJQzA+zaqS0dKHKSuavAgMBAAEC"
                                            "gYAVNPMCbLaZj8UrMxYz9FS+RF/PBBqOi4MLtOvFsM8SpNqS/A/URiWXKUi1ZW63"
                                            "uEzRc4FTtorV4OGqDHy8x8n5E1kEhuihksf/3wrBcBpc76zPxxbd9aTE2hIaAe1r"
                                            "+ccKYOhV75gjQaIiOv3TwC5Twy0W5lqI1ty1Z1s3WgmhAQJBAKiEo8g05Nn9SYOL"
                                            "S1kZx1TBdcYMjxLr8ft2LW5WcWbhCyJnVHS9Cbza4IWeJKcPcbcDRx9NZJfPu8AC"
                                            "mIwCEDkCQQCWdxkvDi+LgB96ym+3B6nR7P2mtDn0kdL/9JEH/FE8c/n0vLXktdy1"
                                            "QVMzkb4W37FlGGY9uoYCsSmu9gAZMd4nAkAE7zVYhGv7EhaX+nkvV7jle3C2ZuG9"
                                            "nRkN0u0LoQ5bA9XuoPXxISPq2sHeR74tAh/DSx5HBV4fr96AhdLvrpPJAkAYclFN"
                                            "K+jdqXtz3+A2xK/6w56Sr0WbTvYRUBMgUQaB4/YApYiIGGQ7rtltz4gq/z07R7OU"
                                            "4/FSDqbPHnj1nvyRAkBfNUfqhqvcgW4TBAWF2NFfRz1MnyNdEnP/KyNTTlsZsTpx"
                                            "MGpkE9z1hLtA0fNrl42xKbBTwrHVzUcLPZf/YohV                        "
                                            "-----END RSA PRIVATE KEY-----                                   ";
        return instance;
    }

    const std::string& getPrivateKey(Person p);
    const std::string& getPublicKey(Person p);

    /**
     * Encrpyt data with RSA of a given person
     */
    const std::string& encryptRsa(const std::string& data, Person p);

    /**
     * Decrpyt data with RSA of a given person
     */
    const std::string& decryptRsa(const std::string& data, Person p);

private:
    RsaHelpers();
    RsaHelpers(RsaHelpers const&);
    void operator=(RsaHelpers const&);

    std::string RSA_PRIVATE_KEY[];
    std::string RSA_PUBLIC_KEY[];
};


#endif