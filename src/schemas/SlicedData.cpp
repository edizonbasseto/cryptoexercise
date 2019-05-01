/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: SlicedData.cpp
 * @Date: Tuesday, 5th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#include <SlicedData.hpp>
#include <string>

namespace Schemas
{
    void to_json(nlohmann::basic_json<>& j, const SlicedData& p) {
        j = nlohmann::basic_json<>{{"key", p.key}, {"substring", p.substring}};
    }

    void from_json(const nlohmann::basic_json<>& j, SlicedData& p) {
        p.key = j.at("key").get<std::string>();
        p.substring = j.at("substring").get<std::string>();
    }

};