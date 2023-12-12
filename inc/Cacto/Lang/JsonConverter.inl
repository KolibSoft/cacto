#include <algorithm>
#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/JsonConverter.hpp>

namespace cacto
{

    template <typename T>
    inline JsonConverter<T>::JsonConverter()
    {
        Converters.push_back(this);
    }

    template <typename T>
    inline JsonConverter<T>::~JsonConverter()
    {
        Converters.erase(std::remove(Converters.begin(), Converters.end(), this), Converters.end());
    }

    template <typename T>
    inline JsonValue JsonConverter<T>::json(const T *const value)
    {
        if (value == nullptr)
            return nullptr;
        for (auto &converter : JsonConverter<T>::Converters)
        {
            JsonValue json = converter->toJson(value);
            if (json != nullptr)
                return std::move(json);
        }
        return nullptr;
    }

    template <typename T>
    inline T *JsonConverter<T>::value(const JsonValue &json)
    {
        if (json == nullptr)
            return nullptr;
        for (auto &converter : JsonConverter<T>::Converters)
        {
            T* value = converter->fromJson(json);
            if (value)
                return value;
        }
        return nullptr;
    }

    template <typename T>
    inline std::vector<const JsonConverter<T> *> JsonConverter<T>::Converters{};

}