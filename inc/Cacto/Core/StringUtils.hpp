#pragma once

#include <string>
#include <Cacto/Core/Export.hpp>

namespace sf
{
    class String;
}

namespace cacto
{

    std::string CACTO_CORE_API getExpression(const sf::String& string);
    sf::String CACTO_CORE_API getString(const std::string &expression);

}