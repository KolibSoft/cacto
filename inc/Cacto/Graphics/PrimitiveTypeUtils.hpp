#pragma once

#include <string>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    std::string CACTO_GRAPHICS_API toString(const sf::PrimitiveType &primitive);
    sf::PrimitiveType CACTO_GRAPHICS_API toPrimitiveType(const std::string &string);

}