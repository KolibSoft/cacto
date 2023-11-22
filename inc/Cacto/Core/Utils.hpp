#ifndef CACTO_CORE_UTILS_HPP
#define CACTO_CORE_UTILS_HPP

#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    using PathMap = std::unordered_map<std::string, std::filesystem::path>;

    JsonValue CACTO_CORE_API pathMapToJson(const PathMap &map);
    void CACTO_CORE_API pathMapFromJson(PathMap &map, const JsonValue &json);

}

#endif