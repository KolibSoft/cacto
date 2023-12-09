#ifndef CACTO_XML_VALUE_HPP
#define CACTO_XML_VALUE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class XmlPrinter;
    class XmlScanner;

    class CACTO_LANG_API XmlValue final
    {

    public:
        enum Kind
        {
            None,
            Text,
            Tag
        };

        Kind getKind() const;

        const std::string &asText() const;
        std::string &asText();

        const std::string &getName() const;
        void setName(const std::string &value);

        const std::unordered_map<std::string, std::string> &asAttributes() const;
        std::unordered_map<std::string, std::string> &asAttributes();

        const std::vector<XmlValue> &asContent() const;
        std::vector<XmlValue> &asContent();

        void print(XmlPrinter &printer) const;
        void scan(XmlScanner &scanner);

        std::string toString(szt identation = 0) const;
        void fromString(const std::string &string);

        void toFile(const std::filesystem::path &path, szt identation = 0) const;
        void fromFile(const std::filesystem::path &path);

        XmlValue(std::nullptr_t = 0);
        XmlValue(const std::string &text);
        XmlValue(const s8t &text);
        XmlValue(const std::string &name, const std::unordered_map<std::string, std::string> &attributes, const std::vector<XmlValue> &content = {});
        XmlValue(const std::string &name, std::initializer_list<std::pair<const std::string, std::string>> attributes, std::initializer_list<XmlValue> content = {});
        virtual ~XmlValue();

        const XmlValue &operator[](szt index) const;
        XmlValue &operator[](szt index);

        const std::string &operator[](const std::string &key) const;
        std::string &operator[](const std::string &key);

        XmlValue(const XmlValue &other);
        XmlValue &operator=(const XmlValue &other);

        XmlValue(XmlValue &&other);
        XmlValue &operator=(XmlValue &&other);

        bool operator==(const XmlValue &other) const;
        bool operator!=(const XmlValue &other) const;

    private:
        struct tag;

        void drop();

        Kind m_kind;
        union
        {
            std::string *m_text;
            tag *m_tag;
        };

        struct tag
        {
            std::string name{};
            std::unordered_map<std::string, std::string> attributes{};
            std::vector<XmlValue> content{};
        };
    };

    template <typename T>
    XmlValue toXml(const T &value) = delete;

    template <typename T>
    void fromXml(T &value, const XmlValue &xml) = delete;

    template <typename T>
    void toXmlFile(const T &value, const std::filesystem::path &path, szt identation = 0);

    template <typename T>
    void fromXmlFile(T &value, const std::filesystem::path &path);

}

#include <Cacto/Lang/XmlValue.inl>

#endif