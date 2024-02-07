#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Core/JsonPack.hpp>
#include <Cacto/Core/JsonUtils.hpp>

namespace cacto
{

    std::string getExpression(const JsonValue &json)
    {
        auto id = getId(json);
        if (id != "")
        {
            auto expression = "@json/" + id;
            return std::move(expression);
        }
        auto expression = json.toString();
        return std::move(expression);
    }

    JsonValue getJson(const std::string &expression)
    {
        if (expression.compare(0, 6, "@json/") == 0)
        {
            auto id = expression.substr(6);
            auto resource = getResource<JsonValue>(id);
            if (resource)
                return *resource;
        }
        JsonValue json = nullptr;
        json.fromString(expression);
        return std::move(json);
    }

}