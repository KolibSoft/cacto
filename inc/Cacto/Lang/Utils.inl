#include <Cacto/Lang/JsonValue.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Lang/Utils.hpp>

namespace cacto
{

    template <typename T>
    inline void toStringFile(const T &value, const std::filesystem::path &path)
    {
        std::string string = toString(value);
        toFile(string, path);
    }

    template <typename T>
    inline void fromStringFile(T &value, const std::filesystem::path &path)
    {
        std::string string{};
        fromFile(string, path);
        fromString(value, string);
    }

    template <typename T>
    inline void toJsonFile(const T &value, const std::filesystem::path &path, szt identation)
    {
        JsonValue json = toJson(value);
        json.toFile(path, identation);
    }

    template <typename T>
    inline void fromJsonFile(T &value, const std::filesystem::path &path)
    {
        JsonValue json = nullptr;
        json.fromFile(path);
        fromJson(value, json);
    }

    template <typename T>
    inline void toXmlFile(const T &value, const std::filesystem::path &path, szt identation)
    {
        XmlValue xml = toXml(value);
        xml.toFile(path, identation);
    }

    template <typename T>
    inline void fromXmlFile(T &value, const std::filesystem::path &path)
    {
        XmlValue xml = nullptr;
        xml.fromFile(path);
        fromXml(value, xml);
    }

}