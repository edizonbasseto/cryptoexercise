/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: ScramblerSliceRequest.hpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#ifndef SCRAMBLER_SLICE_REQUEST_H_
#define SCRAMBLER_SLICE_REQUEST_H_

#include <string>
#include <nlohmann/json.hpp>

namespace Schemas
{
    /**
     * Represents the data of a request when doing a slice operation
     */
    struct ScramblerSliceRequest
    {
        /**
         * The number of slices that has been requested and processed.
         */
        int numberOfSlices;

        /**
         * The slice data hashed with internal crypto algorithm.
         * This slice does contain the slice naming and slice data.
         */
        std::string valueToProcess;
    };

    void to_json(nlohmann::basic_json<>& j, const ScramblerSliceRequest& p);
    void from_json(const nlohmann::basic_json<>& j, ScramblerSliceRequest& p);
};
#endif