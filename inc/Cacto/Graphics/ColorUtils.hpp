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
    sf::Color CACTO_GRAPHICS_API toColor(const std::string &string);

}
