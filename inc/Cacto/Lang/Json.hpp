#ifndef CACTO_JSON_HPP
#define CACTO_JSON_HPP

#include <Cacto/Lang/JsonValue.hpp>

namespace cacto
{

    class Json
    {

    public:
        virtual JsonValue toJson() const = 0;
        virtual void fromJson(const JsonValue &json) = 0;

        Json() = default;
        virtual ~Json() = default;
    };

}

#endif