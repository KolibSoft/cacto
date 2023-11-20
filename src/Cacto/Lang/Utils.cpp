#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/Utils.hpp>

namespace cacto
{

    void replaceAll(std::string &string, const std::string &oldStr, const std::string &newStr)
    {
        szt pos = 0;
        while ((pos = string.find(oldStr, pos)) != std::string::npos)
        {
            string.replace(pos, oldStr.length(), newStr);
            pos += newStr.length();
        }
    }

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