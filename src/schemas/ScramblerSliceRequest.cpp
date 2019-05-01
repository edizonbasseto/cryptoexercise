/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: ScramblerSliceRequest.cpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#include <ScramblerSliceRequest.hpp>

namespace Schemas
{
    void to_json(nlohmann::basic_json<>& j, const ScramblerSliceRequest& p) {
        j = nlohmann::basic_json<>{{"numberOfSlices", p.numberOfSlices}, {"valueToProcess", p.valueToProcess}};
    }

    void from_json(const nlohmann::basic_json<>& j, ScramblerSliceRequest& p) {
        p.numberOfSlices = j.at("numberOfSlices").get<int>();
        p.valueToProcess = j.at("valueToProcess").get<std::string>();
    }

};