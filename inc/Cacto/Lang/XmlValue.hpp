#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <Cacto/Lang/Printable.hpp>
#include <Cacto/Lang/Scannable.hpp>

namespace cacto
{

    enum class XmlType
    {
        Empty,
        Text,
        Tag
    };

    class XmlValue;

    using XmlText = std::string;
    using XmlString = std::string;
    using XmlAttributes = std::unordered_map<XmlString, XmlString>;
    using XmlContent = std::vector<XmlValue>;

    struct CACTO_LANG_API XmlTag
    {
        XmlTag(const XmlString &_name = "", const XmlAttributes &_attributes = {}, const XmlContent &_content = {});
        ~XmlTag();

        XmlString name{};
        XmlAttributes attributes{};
        XmlContent content{};
    };

    class Printer;
    class Scanner;

    class CACTO_LANG_API XmlValue final
        : public virtual Printable,
          public virtual Scannable
    {

    public:
        XmlType getType() const;
        bool isEmpty() const;

        bool isText() const;
        XmlText getText(const XmlText &def = "") const;
        void setText(const XmlText &value = "");
        explicit operator XmlText() const;

        const XmlText &asText() const;
        XmlText &asText();

        bool isTag() const;
        XmlTag getTag(const XmlTag &def = {}) const;
        void setTag(const XmlTag &value = {});
        explicit operator XmlTag() const;

        const XmlTag &asTag() const;
        XmlTag &asTag();

        const XmlString &getName() const;
        void setName(const XmlString &value);
        XmlString getAttribute(const XmlString &name, const XmlString &def = "") const;
        const XmlString &operator[](const XmlString &key) const;
        XmlString &operator[](const XmlString &key);
        const XmlValue &operator[](szt index) const;
        XmlValue &operator[](szt index);

        const XmlAttributes &asAttributes() const;
        XmlAttributes &asAttributes();
        const XmlContent &asContent() const;
        XmlContent &asContent();

        void print(Printer &printer) const override;
        bool scan(Scanner &scanner) override;

        XmlValue(std::nullptr_t = 0);
        XmlValue(const XmlText &text);
        XmlValue(const s8t &text);
        XmlValue(const XmlString &name, const XmlAttributes &attributes, const XmlContent &content = {});
        XmlValue(const XmlString &name, std::initializer_list<std::pair<const XmlString, XmlString>> attributes, std::initializer_list<XmlValue> content = {});
        virtual ~XmlValue();

        XmlValue(const XmlValue &other);
        XmlValue &operator=(const XmlValue &other);

        XmlValue(XmlValue &&other);
        XmlValue &operator=(XmlValue &&other);

        bool operator==(const XmlValue &other) const;
        bool operator!=(const XmlValue &other) const;

        static const XmlValue Empty;
        static const XmlTag NoTag;

    private:
        void drop();

        XmlType m_type;
        union
        {
            XmlText *m_text;
            XmlTag *m_tag;
        };
    };

}
