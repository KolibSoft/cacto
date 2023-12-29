#pragma once

#include <string>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    std::string CACTO_GRAPHICS_API toString(const sf::PrimitiveType &primitive);
    void CACTO_GRAPHICS_API fromString(sf::PrimitiveType &primitive, const std::string &string);

}