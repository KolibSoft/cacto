#include <algorithm>
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
    inline std::vector<const JsonConverter<T> *> JsonConverter<T>::Converters{};

}