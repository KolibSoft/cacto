#include <Cacto/Core/StringPack.hpp>
#include <Cacto/Core/Utils.hpp>

namespace cacto
{

    std::string toAttribute(const sf::String &string)
    {
        auto &id = getId(string);
        if (id != "")
            return id;
        return string.toAnsiString();
    }

    void fromAttribute(sf::String &string, const std::string &attribute)
    {
        auto value = getString(attribute);
        if (value)
            string = *value;
        else
            string = attribute;
    }

}