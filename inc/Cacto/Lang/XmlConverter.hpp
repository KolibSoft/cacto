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
        virtual XmlValue toXml(const Shared<const T> &value) const = 0;
        virtual Shared<T> fromXml(const XmlValue &xml) const = 0;

        XmlConverter();
        virtual ~XmlConverter();

        static XmlValue xml(const Shared<const T> &value);
        static Shared<T> value(const XmlValue &xml);

        static szt getConverterCount();

    private:
        static std::vector<const XmlConverter<T> *> s_Converters;
    };

}

#include <Cacto/Lang/XmlConverter.inl>
