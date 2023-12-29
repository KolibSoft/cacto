#pragma once

#include <vector>
#include <Cacto/Config.hpp>

namespace cacto
{

    class XmlValue;

    template <typename T>
    class XmlConverter
    {

    public:
        virtual XmlValue toXml(const T *const value) const = 0;
        virtual T *fromXml(const XmlValue &xml) const = 0;

        XmlConverter();
        virtual ~XmlConverter();

        static XmlValue xml(const T *const value);
        static T *value(const XmlValue &xml);

        static szt getConverterCount();

    private:
        static std::vector<const XmlConverter<T> *> s_Converters;
    };

}

#include <Cacto/Lang/XmlConverter.inl>
