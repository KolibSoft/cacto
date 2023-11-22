#include <Cacto/Core/Utils.hpp>

namespace cacto
{

    JsonValue pathMapToJson(const PathMap &map)
    {
        auto json = JsonValue::ObjectValue;
        for (auto &pair : map)
            json[pair.first] = pair.second.string();
        return json;
    }

    void pathMapFromJson(PathMap &map, const JsonValue &json)
    {
        map.clear();
        for (auto &pair : json.asObject())
            map[pair.first] = pair.second.asString();
    }

}