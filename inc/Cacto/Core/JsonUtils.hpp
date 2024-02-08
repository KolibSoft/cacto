#pragma once

#include <string>
#include <Cacto/Core/Export.hpp>

namespace cacto
{

    class JsonValue;

    std::string CACTO_CORE_API getExpression(const JsonValue &json);
    JsonValue CACTO_CORE_API getJson(const std::string &expression);

}