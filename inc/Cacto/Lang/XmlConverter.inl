#include <algorithm>
#include <Cacto/Lang/XmlValue.hpp>
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
    inline XmlValue XmlConverter<T>::xml(const T *const value)
    {
        if (value == nullptr)
            return nullptr;
        for (auto &converter : XmlConverter<T>::Converters)
        {
            XmlValue xml = converter->toXml(value);
            if (xml != nullptr)
                return std::move(xml);
        }
        return nullptr;
    }

    template <typename T>
    inline T *XmlConverter<T>::value(const XmlValue &xml)
    {
        if (xml == nullptr)
            return nullptr;
        for (auto &converter : XmlConverter<T>::Converters)
        {
            T *value = converter->fromXml(xml);
            if (value)
                return value;
        }
        return nullptr;
    }

    template <typename T>
    inline std::vector<const XmlConverter<T> *> XmlConverter<T>::Converters{};

}