#pragma once

#include <string>
#include <ostream>
#include <istream>
#include <Cacto/Core/Export.hpp>

namespace sf
{
    class Angle;
}

namespace cacto
{

    std::string CACTO_CORE_API toString(const sf::Angle &angle);
    sf::Angle CACTO_CORE_API toAngle(const std::string &string);

    std::ostream &CACTO_CORE_API operator<<(std::ostream &stream, const sf::Angle &angle);
    std::istream &CACTO_CORE_API operator>>(std::istream &stream, sf::Angle &angle);

}