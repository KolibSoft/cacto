#pragma once

#include <algorithm>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Lang/XmlConverter.hpp>

namespace cacto
{

    template <typename T>
    inline XmlConverter<T>::XmlConverter()
    {
        s_Converters.push_back(this);
    }

    template <typename T>
    inline XmlConverter<T>::~XmlConverter()
    {
        s_Converters.erase(std::remove(s_Converters.begin(), s_Converters.end(), this), s_Converters.end());
    }

    template <typename T>
    inline XmlValue XmlConverter<T>::xml(const T *const value)
    {
        if (value == nullptr)
            return nullptr;
        for (auto &converter : XmlConverter<T>::s_Converters)
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
        for (auto &converter : XmlConverter<T>::s_Converters)
        {
            T *value = converter->fromXml(xml);
            if (value != nullptr)
                return value;
        }
        return nullptr;
    }

    template <typename T>
    inline szt XmlConverter<T>::getConverterCount()
    {
        auto count = XmlConverter<T>::s_Converters.size();
        return count;
    }

    template <typename T>
    inline std::vector<const XmlConverter<T> *> XmlConverter<T>::s_Converters{};

}