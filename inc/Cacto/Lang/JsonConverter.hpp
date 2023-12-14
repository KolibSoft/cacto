#pragma once

#include <vector>

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
        static std::vector<const JsonConverter<T> *> Converters;
    };

}

#include <Cacto/Lang/JsonConverter.inl>