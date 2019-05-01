/*
 * This file, project or its parts can not be copied and/or distributed without
 * the express permission of Edizon Basseto Jr.
 *
 * @file: SlicedData.hpp
 * @Date: Tuesday, 5th March 2019
 * @author: Edizon Basseto Jr (edizon.basseto@outlook.com.br>)
 */
#ifndef SLICEDDATA_H_
#define SLICEDDATA_H_

#include <string>
#include <nlohmann/json.hpp>

namespace Schemas
{
    struct SlicedData
    {
        std::string key;
        std::string substring;
    };

    void to_json(nlohmann::basic_json<>& j, const SlicedData& p);
    void from_json(const nlohmann::basic_json<>& j, SlicedData& p);
}
#endif
