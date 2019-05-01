/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: DescramblerSliceResponse.hpp
 * @Date: Tuesday, 5th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#ifndef DESCRAMBLER_SLICE_RESPONSE_H_
#define DESCRAMBLER_SLICE_RESPONSE_H_

#include <string>
#include <nlohmann/json.hpp>

namespace Schemas
{
    /**
     * Represents the data of a response when joining a slice operation
     */
    struct DescramblerSliceResponse
    {
        /**
         * The unshuffled and uncrypted value
         */
        std::string joinedValue;
    };

    void to_json(nlohmann::basic_json<>& j, const DescramblerSliceResponse& p);
    void from_json(const nlohmann::basic_json<>& j, DescramblerSliceResponse& p);
};
#endif