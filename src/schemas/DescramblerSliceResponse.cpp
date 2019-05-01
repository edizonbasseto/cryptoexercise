/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: ScramblerSliceResponse.cpp
 * @Date: Monday, 4th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#include <DescramblerSliceResponse.hpp>

namespace Schemas
{
    void to_json(nlohmann::basic_json<>& j, const DescramblerSliceResponse& p) {
        j = nlohmann::basic_json<>{{"joinedValue", p.joinedValue}};
    }

    void from_json(const nlohmann::basic_json<>& j, DescramblerSliceResponse& p) {
        p.joinedValue = j.at("joinedValue").get<std::string>();
    }

};