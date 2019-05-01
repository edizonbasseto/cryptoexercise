/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: ScramblerSliceRequest.cpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#include <DescramblerSliceRequest.hpp>

namespace Schemas
{
    void to_json(nlohmann::basic_json<>& j, const DescramblerSliceRequest& p) {
        j = nlohmann::basic_json<>{{"keySlices", p.keySlices}};
    }

    void from_json(const nlohmann::basic_json<>& j, DescramblerSliceRequest& p) {
        p.keySlices = j.at("keySlices").get<std::vector<std::string>>();
    }

};