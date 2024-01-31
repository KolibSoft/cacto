#pragma once

#include <string>
#include <ostream>
#include <istream>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <Cacto/Graphics/Export.hpp>

namespace cacto
{

    std::string CACTO_GRAPHICS_API toString(sf::PrimitiveType primitive);
    sf::PrimitiveType CACTO_GRAPHICS_API toPrimitiveType(const std::string &string);

    std::ostream &CACTO_GRAPHICS_API operator<<(std::ostream &stream, sf::PrimitiveType primitive);
    std::istream &CACTO_GRAPHICS_API operator>>(std::istream &stream, sf::PrimitiveType& primitive);

}