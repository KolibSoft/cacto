#ifndef CACTO_JSON_CONVERTER_HPP
#define CACTO_JSON_CONVERTER_HPP

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

        static JsonValue to(const T *const value);
        static T *from(const JsonValue &json);

    private:
        static std::vector<const JsonConverter<T> *> Converters;
    };

}

#include <Cacto/Lang/JsonConverter.inl>

#endif