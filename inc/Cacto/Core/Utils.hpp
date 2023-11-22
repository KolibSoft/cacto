#ifndef CACTO_CORE_UTILS_HPP
#define CACTO_CORE_UTILS_HPP

#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    using StringMap = std::unordered_map<std::string, std::string>;

    JsonValue CACTO_CORE_API stringMapToJson(const StringMap &map);
    void CACTO_CORE_API stringMapFromJson(StringMap &map, const JsonValue &json);

}

#endif