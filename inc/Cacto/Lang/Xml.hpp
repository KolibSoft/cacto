#ifndef CACTO_XML_HPP
#define CACTO_XML_HPP

#include <filesystem>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class XmlValue;

    class CACTO_LANG_API Xml
    {

    public:
        virtual XmlValue toXml() const = 0;
        virtual void fromXml(const XmlValue &xml) = 0;

        void toFile(const std::filesystem::path &path) const;
        void fromFile(const std::filesystem::path &path);

        Xml() = default;
        virtual ~Xml() = default;
    };

}

#endif