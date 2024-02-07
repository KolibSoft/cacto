#pragma once

#include <string>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class XmlValue;

    std::string CACTO_CORE_API getExpression(const XmlValue &xml);
    XmlValue CACTO_CORE_API getXml(const std::string &expression);

}