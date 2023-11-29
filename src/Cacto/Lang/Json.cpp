#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/Json.hpp>

namespace cacto
{

    void Json::toFile(const std::filesystem::path &path) const
    {
        JsonValue json = nullptr;
        json = toJson();
        json.toFile(path);
    }

    void Json::fromFile(const std::filesystem::path &path)
    {
        JsonValue json = nullptr;
        json.fromFile(path);
        fromJson(json);
    }

}