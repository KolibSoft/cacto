#pragma once

#include <Cacto/Lang/JsonValue.hpp>

namespace cacto
{

    inline bool JsonValue::isNull() const
    {
        return getType() == JsonType::Null;
    }

    inline bool JsonValue::isNumber() const
    {
        return getType() == JsonType::Number;
    }

    inline JsonValue::operator JsonNumber() const
    {
        return getNumber();
    }

    inline bool JsonValue::isString() const
    {
        return getType() == JsonType::String;
    }

    inline JsonValue::operator std::string() const
    {
        return getString();
    }

    inline bool JsonValue::isBoolean() const
    {
        return getType() == JsonType::Boolean;
    }

    inline JsonValue::operator JsonBoolean() const
    {
        return getBoolean();
    }

    inline bool JsonValue::isArray() const
    {
        return getType() == JsonType::Array;
    }

    inline JsonValue::operator JsonArray() const
    {
        return getArray();
    }

    inline bool JsonValue::isObject() const
    {
        return getType() == JsonType::Object;
    }

    inline JsonValue::operator JsonObject() const
    {
        return getObject();
    }

}