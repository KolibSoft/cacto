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

    sf::Color toColor(const std::string &string)
    {
        std::stringstream stream{string};
        stream.get();
        u32t integer;
        stream >> std::hex >> integer;
        sf::Color color{integer};
        return std::move(color);
    }

}
