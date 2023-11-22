#ifndef CACTO_CORE_UTILS_HPP
#define CACTO_CORE_UTILS_HPP

#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    JsonValue CACTO_CORE_API stringMapToJson(const std::unordered_map<std::string, std::string> &map);
    void CACTO_CORE_API stringMapFromJson(std::unordered_map<std::string, std::string> &map, const JsonValue &json);

}

#endif