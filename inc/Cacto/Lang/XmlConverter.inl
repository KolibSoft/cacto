#include <algorithm>
#include <Cacto/Lang/XmlConverter.hpp>

namespace cacto
{

    template <typename T>
    inline XmlConverter<T>::XmlConverter()
    {
        Converters.push_back(this);
    }

    template <typename T>
    inline XmlConverter<T>::~XmlConverter()
    {
        Converters.erase(std::remove(Converters.begin(), Converters.end(), this), Converters.end());
    }

    template <typename T>
    inline std::vector<const XmlConverter<T> *> XmlConverter<T>::Converters{};

}