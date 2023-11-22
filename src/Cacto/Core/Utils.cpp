#include <Cacto/Core/Utils.hpp>

namespace cacto
{

    JsonValue stringMapToJson(const StringMap &map)
    {
        auto json = JsonValue::ObjectValue;
        for (auto &pair : map)
            json[pair.first] = pair.second;
        return json;
    }

    void stringMapFromJson(StringMap &map, const JsonValue &json)
    {
        map.clear();
        for (auto &pair : json.asObject())
            map[pair.first] = pair.second.asString();
    }

}