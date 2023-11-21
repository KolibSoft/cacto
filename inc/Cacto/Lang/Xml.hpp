#ifndef CACTO_XML_HPP
#define CACTO_XML_HPP

#include <Cacto/Lang/XmlValue.hpp>

namespace cacto
{

    class CACTO_LANG_API Xml
    {

    public:
        virtual XmlValue toXml() const = 0;
        virtual void fromXml(const XmlValue &xml) = 0;

        Xml() = default;
        virtual ~Xml() = default;
    };

}

#endif