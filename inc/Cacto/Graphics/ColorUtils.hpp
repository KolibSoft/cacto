#pragma once

#include <string>
#include <ostream>
#include <istream>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Color;
}

namespace cacto
{

    std::string CACTO_GRAPHICS_API toString(const sf::Color &color);
    sf::Color CACTO_GRAPHICS_API toColor(const std::string &string);

    std::ostream &CACTO_GRAPHICS_API operator<<(std::ostream &stream, const sf::Color &color);
    std::istream &CACTO_GRAPHICS_API operator>>(std::istream &stream, sf::Color &color);

    std::string CACTO_GRAPHICS_API getExpression(const sf::Color& color);
    sf::Color CACTO_GRAPHICS_API getColor(const std::string &expression);

}
