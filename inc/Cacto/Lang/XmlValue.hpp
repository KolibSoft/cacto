#pragma once

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

        bool isText() const;
        std::string getText(const std::string &def = "") const;
        const std::string &asText() const;
        std::string &asText();

        bool isTag() const;
        const std::string &getName() const;
        void setName(const std::string &value);

        std::string getAttribute(const std::string &name, const std::string &def = "") const;
        const std::unordered_map<std::string, std::string> &asAttributes() const;
        std::unordered_map<std::string, std::string> &asAttributes();
        const std::string &operator[](const std::string &key) const;
        std::string &operator[](const std::string &key);

        const std::vector<XmlValue> &asContent() const;
        std::vector<XmlValue> &asContent();
        const XmlValue &operator[](szt index) const;
        XmlValue &operator[](szt index);

        void print(XmlPrinter &printer) const;
        void scan(XmlScanner &scanner);

        void toStream(std::ostream &stream, szt identation = 0) const;
        void fromStream(std::istream &stream);

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

        XmlValue(const XmlValue &other);
        XmlValue &operator=(const XmlValue &other);

        XmlValue(XmlValue &&other);
        XmlValue &operator=(XmlValue &&other);

        bool operator==(const XmlValue &other) const;
        bool operator!=(const XmlValue &other) const;

        static const XmlValue NoneValue;
        static const XmlValue TextValue;
        static const XmlValue TagValue;

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

    std::ostream &CACTO_LANG_API operator<<(std::ostream &stream, const XmlValue &xml);
    std::istream &CACTO_LANG_API operator>>(std::istream &stream, XmlValue &xml);

}
