/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: SliceBusiness.cpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */

#include <SliceBusiness.hpp>

/**
 * Using to initialize rando pseudo generator, aviding memory leak
 */
std::random_device rd("/dev/urandom");

Schemas::DescramblerSliceResponse SliceBusiness::DescrambleData(const Schemas::DescramblerSliceRequest& request)
{
    int slices = request.keySlices.size();
    int keyNames = SPLIT_NAMING.size();

    std::vector<Schemas::SlicedData> dcvalues;
    Schemas::DescramblerSliceResponse response;

    //First decrypt to avoid decrypting too many times.
    for (int i=0; i<slices; i++)
    {
        try
        {
            nlohmann::basic_json<> j = nlohmann::basic_json<>::parse(this->decryptJson(request.keySlices[i]));
            dcvalues.push_back(j.get<Schemas::SlicedData>());
        }
        catch(...)
        {
            return response;
        }
    }

    for (int i=0; i<keyNames; i++)
    {
        for(int x=0; x<slices; x++)
        {
            if (SPLIT_NAMING[i] == dcvalues[x].key)
            {
                response.joinedValue.append(dcvalues[x].substring);
                break;
            }
        }
    }
    return response;
}

Schemas::ScramblerSliceResponse SliceBusiness::scrambleData(const Schemas::ScramblerSliceRequest& request)
{
    std::string data = request.valueToProcess;
    int numberOfSlices = request.numberOfSlices;

    if (data.length() < numberOfSlices)
    {
        throw "The division cannot be done, as the value length is lower than the number of divisions requested.";
    }
    std::vector<Schemas::SlicedData> slicedData = this->sliceData(data, numberOfSlices);
    std::vector<Schemas::SlicedData> shuffled = this->shuffleData(slicedData);
    Schemas::ScramblerSliceResponse responseObject = this->prepareResponseEncrypted(shuffled);
    return responseObject;
}

Schemas::ScramblerSliceResponse SliceBusiness::prepareResponseEncrypted(const std::vector<Schemas::SlicedData> &shuffled)
{
    Schemas::ScramblerSliceResponse ret;
    const int slices = shuffled.size();

    ret.numberOfSlices = slices;

    for (int i=0; i<slices; i++)
    {
        nlohmann::basic_json<> js = shuffled[i];
        ret.scrambledData.push_back( this->encryptJson(js.dump()));
    }

    return ret;
}

std::string SliceBusiness::encryptJson(const std::string& data)
{
    //Crypto PP deal with the new created. Don't worry about deletes...
    //https://stackoverflow.com/questions/42545105/crypto-explicit-destruction-during-encryption-decryption
    std::string str_out;
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryption((CryptoPP::byte*)CRYPT_KEY.c_str(), CRYPT_KEY.length(),(CryptoPP::byte*)IV.c_str());
    CryptoPP::StringSource encryptor(data, true,
        new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::Base64Encoder(
                new CryptoPP::StringSink(str_out), false)
        )
    );
    return str_out;
}

std::string SliceBusiness::decryptJson(const std::string& data)
{
    //Crypto PP deal with the new created. Don't worry about deletes...
    //https://stackoverflow.com/questions/42545105/crypto-explicit-destruction-during-encryption-decryption
    std::string str_out;
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption((CryptoPP::byte*)CRYPT_KEY.c_str(), CRYPT_KEY.length(), (CryptoPP::byte*)IV.c_str());

    CryptoPP::StringSource decryptor(data, true,
        new CryptoPP::Base64Decoder(
            new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::StringSink(str_out))
        )
    );
    return str_out;
}

std::vector<Schemas::SlicedData> SliceBusiness::shuffleData(const std::vector<Schemas::SlicedData>& slicedData)
{
    std::vector<Schemas::SlicedData> ret;
    std::vector<int> randomvalues;
    const int maxRandom = slicedData.size()-1;

    //Random generator using the random_device.
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distributor(0, maxRandom);
    int random = distributor(gen);

    for (int i=0; i<=maxRandom; i++)
    {
        while (!randomvalues.empty() &&
            std::find(randomvalues.begin(), randomvalues.end(), random) != randomvalues.end())
        {
            random = distributor(gen);
        }
        randomvalues.push_back(random);
        ret.push_back(slicedData[random]);
    }

    return ret;
}

void SliceBusiness::verifyLastChar(const std::string& substring, int& substringSize)
{
    std::string lastString(1,substring.back());

    std::regex isSpecial("\\w+");
    if (!std::regex_match(lastString, isSpecial))
    {
        substringSize++;
        verifyLastChar(substring.substr(0, substring.length()-1), substringSize);
    }

    return;
}

std::vector<Schemas::SlicedData> SliceBusiness::sliceData(const std::string& fullstring, const int slices)
{
    const int stringSize = fullstring.length();
    int substringSize = fullstring.length()/slices;

    std::vector<Schemas::SlicedData> ret;

    int substringStart = 0;
    for( int i=0; i<slices; i++)
    {
        Schemas::SlicedData d;
        d.key = SPLIT_NAMING[i];

        if(slices-1 == i)
        {
            substringSize = fullstring.length();
        }

        //Avoiding problems with special chars in the last position of split.
        //this->verifyLastChar(fullstring.substr(substringStart, substringSize), substringSize);

        if(substringSize > stringSize)
        {
            throw "Too many special characters on the string or ending with one.";
        }

        if ((substringSize + substringStart) >= stringSize)
        {
            substringSize = fullstring.length();
        }

        d.substring = fullstring.substr(substringStart, substringSize);
        substringStart += substringSize;

        substringSize = fullstring.length()/slices;

        ret.push_back(d);
    }
    return ret;
}

SliceBusiness::~SliceBusiness()
{
    SPLIT_NAMING.~vector();
}