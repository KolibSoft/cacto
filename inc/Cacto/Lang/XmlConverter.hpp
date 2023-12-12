#ifndef CACTO_XML_CONVERTER_HPP
#define CACTO_XML_CONVERTER_HPP

#include <vector>

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

    private:
        static std::vector<const XmlConverter<T> *> Converters;
    };

}

#include <Cacto/Lang/XmlConverter.inl>

#endif