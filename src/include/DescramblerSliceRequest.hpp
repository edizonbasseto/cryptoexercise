/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: DescramblerSliceRequest.hpp
 * @Date: Tuesday, 5th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#ifndef DESCRAMBLER_SLICE_REQUEST_H_
#define DESCRAMBLER_SLICE_REQUEST_H_

#include <string>
#include <nlohmann/json.hpp>

namespace Schemas
{
    /**
     * Represents the data of response when doing a slice operation
     */
    struct DescramblerSliceRequest
    {
        /**
         * The sliced and scrambled data hashed with internal crypto algorithm.
         * This data must contain the slice naming and substring data.
         */
        std::vector<std::string> keySlices;
    };
    void to_json(nlohmann::basic_json<>& j, const DescramblerSliceRequest& p);
    void from_json(const nlohmann::basic_json<>& j, DescramblerSliceRequest& p);
};
#endif