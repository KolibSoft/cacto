#pragma once

#include <vector>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class JsonValue;

    template <typename T>
    class JsonConverter
    {

    public:
        virtual JsonValue toJson(const T *const value) const = 0;
        virtual T *fromJson(const JsonValue &json) const = 0;

        JsonConverter();
        virtual ~JsonConverter();

        static JsonValue json(const T *const value);
        static T *value(const JsonValue &json);

    private:
        static std::vector<const JsonConverter<T> *> s_Converters;
    };

    template <typename T>
    JsonValue toJson(const T *const value);

    template <typename T>
    T *fromJson(const JsonValue &json);

}

#include <Cacto/Lang/JsonConverter.inl>