#include <algorithm>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/JsonConverter.hpp>

namespace cacto
{

    template <typename T>
    inline JsonConverter<T>::JsonConverter()
    {
        s_Converters.push_back(this);
    }

    template <typename T>
    inline JsonConverter<T>::~JsonConverter()
    {
        s_Converters.erase(std::remove(s_Converters.begin(), s_Converters.end(), this), s_Converters.end());
    }

    template <typename T>
    inline JsonValue JsonConverter<T>::json(const Shared<const T> &value)
    {
        if (value == nullptr)
            return nullptr;
        for (auto &converter : JsonConverter<T>::s_Converters)
        {
            JsonValue json = converter->toJson(value);
            if (json != nullptr)
                return std::move(json);
        }
        return nullptr;
    }

    template <typename T>
    inline Shared<T> JsonConverter<T>::value(const JsonValue &json)
    {
        if (json == nullptr)
            return nullptr;
        for (auto &converter : JsonConverter<T>::s_Converters)
        {
            T *value = converter->fromJson(json);
            if (value)
                return std::move(value);
        }
        return nullptr;
    }

    template <typename T>
    inline szt JsonConverter<T>::getConverterCount()
    {
        auto count = JsonConverter<T>::s_Converters.size();
        return count;
    }

    template <typename T>
    inline std::vector<const JsonConverter<T> *> JsonConverter<T>::s_Converters{};

}