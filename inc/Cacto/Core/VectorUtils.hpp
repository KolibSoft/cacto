#pragma once

#include <string>
#include <ostream>
#include <istream>
#include <SFML/System/Vector2.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    std::string CACTO_CORE_API toString(const sf::Vector2f &vector);
    sf::Vector2f CACTO_CORE_API toVector(const std::string &string);

    std::ostream &CACTO_CORE_API operator<<(std::ostream &stream, const sf::Vector2f &vector);
    std::istream &CACTO_CORE_API operator>>(std::istream &stream, sf::Vector2f &vector);

}