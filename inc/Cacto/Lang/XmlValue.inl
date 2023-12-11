#include <Cacto/Lang/XmlValue.hpp>

namespace cacto
{

    template <typename T>
    inline void toXmlFile(const T &value, const std::filesystem::path &path, szt identation)
    {
        auto xml = toXml<T>(value);
        xml.toFile(path, identation);
    }

    template <typename T>
    inline T fromXmlFile(const std::filesystem::path &path)
    {
        XmlValue xml = nullptr;
        xml.fromFile(path);
        auto value = fromXml<T>(xml);
        return std::move(value);
    }

}