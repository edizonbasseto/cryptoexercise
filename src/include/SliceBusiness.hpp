/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: SliceBusiness.h
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#ifndef SLICEBUSINESS_H_
#define SLICEBUSINESS_H_

#include <string>
#include <ScramblerSliceResponse.hpp>
#include <ScramblerSliceRequest.hpp>
#include <DescramblerSliceRequest.hpp>
#include <DescramblerSliceResponse.hpp>
#include <SlicedData.hpp>
#include <random>
#include <iostream>
#include <aes.h>
#include <filters.h>
#include <modes.h>
#include <base64.h>
#include <regex>

// To correct order the keys after shuffling it.
const static std::vector<std::string> SPLIT_NAMING {"banana", "pera", "uva", "maca", "saladamista", "mequetrefe"};

// This should be so hard to descompile, that I'm will not take care of those keys.
// Indeed those keys are only to transform a JSON payload into a single BASE64 string.
// It's not to hard encrypt data.
const static std::string CRYPT_KEY {"VkYp3s6v9y$B&E)H@MbQeThWmZq4t7w!"};
const static std::string IV = "2536985214525822";
/**
 * Contains all Slice Business Logic
 */
class SliceBusiness
{
 public:
    /**
     * Will split a given data into the requested parts. After slipitting it will
     * Scramble and return.
     */
    Schemas::ScramblerSliceResponse scrambleData(const Schemas::ScramblerSliceRequest& request);

    /**
     * Will split a given data into the requested parts. After slipitting it will
     * descramble and return.
     */
    Schemas::DescramblerSliceResponse DescrambleData(const Schemas::DescramblerSliceRequest& request);

    ~SliceBusiness();

    private:

    /**
     * Encrypt a given json
     */
    std::string encryptJson(const std::string& j);

    /**
     * Decrypt a given json
     */
    std::string decryptJson(const std::string& j);

    /**
     * Within the given shuffled data, encrypt the values before returning to other service.
    */
    Schemas::ScramblerSliceResponse prepareResponseEncrypted(const std::vector<Schemas::SlicedData> &shuffled);

    /**
     * Based on the number of slices, slice the full string
     */
    std::vector<Schemas::SlicedData> sliceData(const std::string& fullstring, const int slices);

    /**
     * Based on the sliced data it will shuffle the positions and change key index to a fixed key.
     */
    std::vector<Schemas::SlicedData> shuffleData(const std::vector<Schemas::SlicedData>& slicedData);

    /**
     * Avoiding problems with special chars at last word position when data is split.
     */
    void verifyLastChar(const std::string &substring, int &substringSize);
};
#endif