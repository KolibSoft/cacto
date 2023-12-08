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

        JsonConverter() = default;
        virtual ~JsonConverter() = default;

        static std::vector<const JsonConverter<T>*> Converters;
    };

    template <typename T>
    inline std::vector<const JsonConverter<T>*> JsonConverter<T>::Converters{};

}

#endif