#include <Cacto/Lang/XmlValue.hpp>

namespace cacto
{

    template <typename T>
    inline void toXmlFile(const T &value, const std::filesystem::path &path)
    {
        XmlValue xml = toXml(value);
        xml.toFile(path);
    }

    template <typename T>
    inline void fromXmlFile(T &value, const std::filesystem::path &path)
    {
        XmlValue xml = nullptr;
        xml.fromFile(path);
        fromXml(value, xml);
    }

}