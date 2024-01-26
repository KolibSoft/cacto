#pragma once

#include <string>
#include <ostream>
#include <istream>
#include <SFML/System/Time.hpp>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    std::string CACTO_CORE_API toString(const sf::Time &time);
    sf::Time CACTO_CORE_API toTime(const std::string &string);

    std::ostream &CACTO_CORE_API operator<<(std::ostream &stream, const sf::Time &time);
    std::istream &CACTO_CORE_API operator>>(std::istream &stream, sf::Time &time);

}