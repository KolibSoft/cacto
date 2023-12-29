#include <sstream>
#include <SFML/Graphics/Color.hpp>
#include <Cacto/Graphics/ColorPack.hpp>
#include <Cacto/Graphics/ColorUtils.hpp>

namespace cacto
{

    std::string toString(const sf::Color &color)
    {
        std::stringstream stream{};
        stream << '#' << std::hex << std::setw(8) << std::setfill('0') << std::uppercase << color.toInteger();
        return stream.str();
    }

    void fromString(sf::Color &color, const std::string &string)
    {
        std::stringstream stream{string};
        stream.get();
        u32t integer;
        stream >> std::hex >> integer;
        color = sf::Color(integer);
    }

    std::string toAttribute(const sf::Color &color)
    {
        auto &id = getId(color);
        if (id != "")
            return id;
        return toString(color);
    }

    void fromAttribute(sf::Color &color, const std::string &attribute)
    {
        auto value = getColor(attribute);
        if (value)
            color = *value;
        else
            fromString(color, attribute);
    }

}
