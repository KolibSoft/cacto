#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Lang/Xml.hpp>

namespace cacto
{

    void Xml::toFile(const std::filesystem::path &path) const
    {
        XmlValue xml = nullptr;
        xml = toXml();
        xml.toFile(path);
    }

    void Xml::fromFile(const std::filesystem::path &path)
    {
        XmlValue xml = nullptr;
        xml.fromFile(path);
        fromXml(xml);
    }

}