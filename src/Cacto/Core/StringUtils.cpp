#include <SFML/System/String.hpp>
#include <Cacto/Core/StringPack.hpp>
#include <Cacto/Core/StringUtils.hpp>

namespace cacto
{

    std::string CACTO_CORE_API getExpression(const sf::String &string)
    {
        auto id = getId(string);
        if (id != "")
        {
            auto expression = "@string/" + id;
            return std::move(expression);
        }
        return string.toAnsiString();
    }

    sf::String getString(const std::string &expression)
    {
        if (expression.compare(0, 8, "@string/") == 0)
        {
            auto id = expression.substr(8);
            auto resource = getResource<sf::String>(id);
            if (resource)
                return *resource;
        }
        return expression;
    }

}