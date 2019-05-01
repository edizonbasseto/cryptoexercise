/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: ScramblerSliceResponse.hpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#ifndef SCRAMBLER_SLICE_RESPONSE_H_
#define SCRAMBLER_SLICE_RESPONSE_H_

#include <string>
#include <nlohmann/json.hpp>

namespace Schemas
{
    /**
     * Represents the data of response when doing a slice operation
     */
    struct ScramblerSliceResponse
    {
        /**
         * The number of slices that has been requested and processed.
         */
        int numberOfSlices;

        /**
         * The sliced and scrambled data hashed with internal crypto algorithm.
         * This data does contain the slice naming and substring data.
         */
        std::vector<std::string> scrambledData;
    };
    void to_json(nlohmann::basic_json<>& j, const ScramblerSliceResponse& p);
    void from_json(const nlohmann::basic_json<>& j, ScramblerSliceResponse& p);
};
#endif