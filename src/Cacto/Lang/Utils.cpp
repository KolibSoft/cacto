#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/Utils.hpp>

namespace cacto
{

    void stringMapToFile(const std::unordered_map<std::string, std::string> &map, const std::filesystem::path &path)
    {
        auto json = JsonValue::ObjectValue;
        for (auto &pair : map)
            json[pair.first] = pair.second;
        json.toFile(path);
    }

    std::unordered_map<std::string, std::string> stringMapFromFile(const std::filesystem::path &path)
    {
        JsonValue json = nullptr;
        json.fromFile(path);
        std::unordered_map<std::string, std::string> map{};
        for (auto &pair : json.asObject())
            map[pair.first] = pair.second.asString();
        return map;
    }

}