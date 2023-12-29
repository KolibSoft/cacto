#pragma once

#include <string>
#include <Cacto/Graphics/Export.hpp>

namespace sf
{
    class Color;
}

namespace cacto
{

    std::string CACTO_GRAPHICS_API toString(const sf::Color &color);
    void CACTO_GRAPHICS_API fromString(sf::Color &color, const std::string &string);

    std::string CACTO_GRAPHICS_API toAttribute(const sf::Color &color);
    void CACTO_GRAPHICS_API fromAttribute(sf::Color &color, const std::string &attribute);

}
