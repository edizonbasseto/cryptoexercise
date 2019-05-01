/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: ScramblerSliceResponse.cpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#include <ScramblerSliceResponse.hpp>

namespace Schemas
{
    void to_json(nlohmann::basic_json<>& j, const ScramblerSliceResponse& p) {
        j = nlohmann::basic_json<>{{"numberOfSlices", p.numberOfSlices}, {"scrambledData", p.scrambledData}};
    }

    void from_json(const nlohmann::basic_json<>& j, ScramblerSliceResponse& p) {
        p.numberOfSlices = j.at("numberOfSlices").get<int>();
        p.scrambledData = j.at("scrambledData").get<std::vector<std::string>>();
    }

};