#pragma once

#include <string>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    std::string CACTO_CORE_API toAttribute(const sf::String &string);
    void CACTO_CORE_API fromAttribute(sf::String &string, const std::string &attribute);

}
