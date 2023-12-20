#pragma once

#include <vector>
#include <Cacto/Config.hpp>

namespace cacto
{

    class JsonValue;

    template <typename T>
    class JsonConverter
    {

    public:
        virtual JsonValue toJson(const Shared<const T> &value) const = 0;
        virtual Shared<T> fromJson(const JsonValue &json) const = 0;

        JsonConverter();
        virtual ~JsonConverter();

        static JsonValue json(const Shared<const T> &value);
        static Shared<T> value(const JsonValue &json);

        static szt getConverterCount();

    private:
        static std::vector<const JsonConverter<T> *> s_Converters;
    };

}

#include <Cacto/Lang/JsonConverter.inl>