#include <stdexcept>
#include <fstream>
#include <Cacto/Lang/XmlPrinter.hpp>
#include <Cacto/Lang/XmlScanner.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Lang/Utils.hpp>

namespace cacto
{

    XmlValue::Kind XmlValue::getKind() const
    {
        return m_kind;
    }

    bool XmlValue::isText() const
    {
        return m_kind == Text;
    }

    std::string XmlValue::getText(const std::string &def) const
    {
        if (m_kind != Text)
            return def;
        return *m_text;
    }

    const std::string &XmlValue::asText() const
    {
        if (m_kind != Text)
            throw std::runtime_error("Xml is not an text value");
        return *m_text;
    }

    std::string &XmlValue::asText()
    {
        if (m_kind != Text)
            throw std::runtime_error("Xml is not an text value");
        return *m_text;
    }

    bool XmlValue::isTag() const
    {
        return m_kind == Tag;
    }

    const std::string &XmlValue::getName() const
    {
        if (m_kind != Tag)
            throw std::runtime_error("Xml is not an tag value");
        return m_tag->name;
    }

    void XmlValue::setName(const std::string &value)
    {
        if (m_kind != Tag)
            throw std::runtime_error("Xml is not an tag value");
        m_tag->name = value;
    }

    std::string XmlValue::getAttribute(const std::string &name, const std::string &def) const
    {
        if (m_kind != Tag)
            return def;
        for (auto &pair : m_tag->attributes)
            if (pair.first == name)
                return pair.second;
        return def;
    }

    const std::unordered_map<std::string, std::string> &XmlValue::asAttributes() const
    {
        if (m_kind != Tag)
            throw std::runtime_error("Xml is not an tag value");
        return m_tag->attributes;
    }

    const std::string &XmlValue::operator[](const std::string &key) const
    {
        if (m_kind != Tag)
            throw std::runtime_error("Xml is not an tag value");
        return m_tag->attributes.at(key);
    }

    std::string &XmlValue::operator[](const std::string &key)
    {
        if (m_kind != Tag)
            throw std::runtime_error("Xml is not an tag value");
        return m_tag->attributes[key];
    }

    std::unordered_map<std::string, std::string> &XmlValue::asAttributes()
    {
        if (m_kind != Tag)
            throw std::runtime_error("Xml is not an tag value");
        return m_tag->attributes;
    }

    const std::vector<XmlValue> &XmlValue::asContent() const
    {
        if (m_kind != Tag)
            throw std::runtime_error("Xml is not an tag value");
        return m_tag->content;
    }

    std::vector<XmlValue> &XmlValue::asContent()
    {
        if (m_kind != Tag)
            throw std::runtime_error("Xml is not an tag value");
        return m_tag->content;
    }

    const XmlValue &XmlValue::operator[](szt index) const
    {
        if (m_kind != Tag)
            return NoneValue;
        if (index >= m_tag->content.size())
            return NoneValue;
        return m_tag->content.at(index);
    }

    XmlValue &XmlValue::operator[](szt index)
    {
        if (m_kind != Tag)
            throw std::runtime_error("Xml is not an tag value");
        return m_tag->content[index];
    }

    void XmlValue::print(XmlPrinter &printer) const
    {
        switch (m_kind)
        {
        case None:
            break;
        case Text:
            printer.printText(*m_text);
            break;
        case Tag:
            printer.print("<");
            printer.printName(m_tag->name);
            if (m_tag->attributes.size() > 0)
            {
                if (printer.getIdentation() > 0)
                {
                    printer.ident();
                    printer.println();
                }
                else
                    printer.print(" ");
                for (auto &pair : m_tag->attributes)
                {
                    printer.printAttribute(pair.first);
                    printer.print("=");
                    printer.printValue(pair.second);
                    if (printer.getIdentation() > 0)
                        printer.println();
                    else
                        printer.print(" ");
                }
                if (printer.getIdentation() > 0)
                    printer.backspaceln();
            }
            if (m_tag->content.size() > 0)
            {
                if (m_tag->attributes.size() == 0)
                    printer.ident();
                printer.print(">");
                if (printer.getIdentation() > 0)
                    printer.println();
                for (auto &value : m_tag->content)
                {
                    value.print(printer);
                    if (printer.getIdentation() > 0)
                        printer.println();
                }
                if (printer.getIdentation() > 0)
                    printer.backspaceln();
                if (printer.getIdentation() > 0)
                {
                    printer.dedent();
                    printer.println();
                }
                printer.print("</");
                printer.printName(m_tag->name);
                printer.print(">");
            }
            else
            {
                printer.print(" />");
                if (m_tag->attributes.size() > 0 && printer.getIdentation() > 0)
                    printer.dedent();
            }
            break;
        }
    }

    void XmlValue::scan(XmlScanner &scanner)
    {
        drop();
        scanner.dropBlank();
        if (scanner.scanText())
        {
            auto token = scanner.take();
            m_kind = Text;
            m_text = new std::string(token);
            replace(*m_text, "&lt;", "<");
            replace(*m_text, "&gt;", ">");
            replace(*m_text, "&quot;", "\"");
            replace(*m_text, "&pos;", "\'");
            replace(*m_text, "&amp;", "&");
            return;
        }
        if (scanner.dropToken("<"))
        {
            m_kind = Tag;
            m_tag = new tag();
            scanner.dropBlank();
            if (!scanner.scanName())
                throw std::runtime_error("XML parse error: expected tag name");
            auto token = scanner.take();
            m_tag->name = token;
            scanner.dropBlank();
            if (scanner.dropToken("/>"))
                return;
            if (!scanner.dropToken(">"))
            {
            attribute_item:
                scanner.dropBlank();
                if (!scanner.scanAttribute())
                    throw std::runtime_error("XML parse error: expected attribute name");
                token = scanner.take();
                auto name = token;
                scanner.dropBlank();
                if (!scanner.dropToken("="))
                    throw std::runtime_error("XML parse error: expected '='");
                scanner.dropBlank();
                if (!scanner.scanValue())
                    throw std::runtime_error("XML parse error: expected attribute value");
                token = scanner.take();
                auto value = token.substr(1, token.size() - 2);
                m_tag->attributes[name] = value;
                scanner.dropBlank();
                if (scanner.dropToken("/>"))
                    return;
                if (!scanner.dropToken(">"))
                    goto attribute_item;
            }
            scanner.dropBlank();
            if (!scanner.dropToken("</"))
            {
            content_item:
                m_tag->content.push_back(nullptr);
                m_tag->content.back().scan(scanner);
                scanner.dropBlank();
                if (!scanner.dropToken("</"))
                    goto content_item;
            }
            scanner.dropBlank();
            if (!scanner.dropToken(m_tag->name))
                throw std::runtime_error("XML parse error: expected close tag name");
            scanner.dropBlank();
            if (!scanner.dropToken(">"))
                throw std::runtime_error("XML parse error: expected '>'");
            return;
        }
        throw std::runtime_error("XML parse error: unknown value");
    }

    std::string XmlValue::toString(szt identation) const
    {
        std::string string{};
        XmlPrinter printer{};
        printer.setStream(&string);
        printer.setIdentation(identation);
        print(printer);
        return string;
    }

    void XmlValue::fromString(const std::string &string)
    {
        XmlScanner scanner{};
        scanner.setStream(&string);
        scan(scanner);
    }

    void XmlValue::toFile(const std::filesystem::path &path, szt identation) const
    {
        auto string = toString(identation);
        cacto::toFile(string, path);
    }

    void XmlValue::fromFile(const std::filesystem::path &path)
    {
        std::string string{};
        cacto::fromFile(string, path);
        fromString(string);
    }

    XmlValue::XmlValue(std::nullptr_t)
        : m_kind(None),
          m_text(nullptr)
    {
    }

    XmlValue::XmlValue(const std::string &text)
        : m_kind(Text),
          m_text(new std::string(text))
    {
    }

    XmlValue::XmlValue(const s8t &text)
        : m_kind(Text),
          m_text(new std::string(text))
    {
    }

    XmlValue::XmlValue(const std::string &name, const std::unordered_map<std::string, std::string> &attributes, const std::vector<XmlValue> &content)
        : m_kind(Tag),
          m_tag(new tag())
    {
        m_tag->name = name;
        m_tag->attributes = attributes;
        m_tag->content = content;
    }

    XmlValue::XmlValue(const std::string &name, std::initializer_list<std::pair<const std::string, std::string>> attributes, std::initializer_list<XmlValue> content)
        : m_kind(Tag),
          m_tag(new tag())
    {
        m_tag->name = name;
        m_tag->attributes = attributes;
        m_tag->content = content;
    }

    XmlValue::~XmlValue()
    {
        drop();
    }

    XmlValue::XmlValue(const XmlValue &other)
        : m_kind(other.m_kind)
    {
        switch (m_kind)
        {
        case None:
            m_text = nullptr;
            break;
        case Text:
            m_text = new std::string(*other.m_text);
            break;
        case Tag:
            m_tag = new tag();
            m_tag->name = other.m_tag->name;
            m_tag->attributes = other.m_tag->attributes;
            m_tag->content = other.m_tag->content;
            break;
        }
    }

    XmlValue &XmlValue::operator=(const XmlValue &other)
    {
        auto copy = XmlValue(other);
        *this = std::move(copy);
        return *this;
    }

    XmlValue::XmlValue(XmlValue &&other)
    {
        *this = std::move(other);
    }

    XmlValue &XmlValue::operator=(XmlValue &&other)
    {
        drop();
        m_kind = other.m_kind;
        switch (m_kind)
        {
        case None:
            m_text = nullptr;
            break;
        case Text:
            m_text = other.m_text;
            break;
        case Tag:
            m_tag = other.m_tag;
            break;
        }
        other.m_kind = None;
        other.m_text = nullptr;
        return *this;
    }

    bool XmlValue::operator==(const XmlValue &other) const
    {
        if (m_kind == other.m_kind)
        {
            switch (m_kind)
            {
            case None:
                return true;
            case Text:
                return *m_text == *other.m_text;
            case Tag:
                return m_tag->name == other.m_tag->name && m_tag->attributes == other.m_tag->attributes && m_tag->content == other.m_tag->content;
            }
        }
        return false;
    }

    bool XmlValue::operator!=(const XmlValue &other) const
    {
        return !(*this == other);
    }

    const XmlValue XmlValue::NoneValue = nullptr;
    const XmlValue XmlValue::TextValue = "";
    const XmlValue XmlValue::TagValue = {"", {}};

    void XmlValue::drop()
    {
        switch (m_kind)
        {
        case Text:
            delete m_text;
            break;
        case Tag:
            delete m_tag;
            break;
        default:
            break;
        }
        m_kind = None;
        m_text = nullptr;
    }

}