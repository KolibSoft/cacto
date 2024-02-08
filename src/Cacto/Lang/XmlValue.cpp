#include <stdexcept>
#include <fstream>
#include <Cacto/Lang/XmlPrinter.hpp>
#include <Cacto/Lang/XmlScanner.hpp>
#include <Cacto/Lang/XmlValue.hpp>

namespace cacto
{

    XmlTag::XmlTag(const XmlString &_name, const XmlAttributes &_attributes, const XmlContent &_content)
        : name(_name),
          attributes(_attributes),
          content(_content)
    {
    }

    XmlTag::~XmlTag() = default;

    XmlType XmlValue::getType() const
    {
        return m_type;
    }

    bool XmlValue::isEmpty() const
    {
        return m_type == XmlType::Empty;
    }

    bool XmlValue::isText() const
    {
        return m_type == XmlType::Text;
    }

    XmlText XmlValue::getText(const XmlText &def) const
    {
        if (m_type != XmlType::Text)
            return def;
        return *m_text;
    }

    void XmlValue::setText(const XmlText &value)
    {
        if (m_type == XmlType::Text)
            *m_text = value;
        else
        {
            drop();
            m_type = XmlType::Text;
            m_text = new XmlText(value);
        }
    }

    XmlValue::operator XmlText() const
    {
        return getText();
    }

    const XmlText &XmlValue::asText() const
    {
        if (m_type != XmlType::Text)
            return EmptyText;
        return *m_text;
    }

    XmlText &XmlValue::asText()
    {
        if (m_type != XmlType::Text)
            throw std::runtime_error("Xml is not an text value");
        return *m_text;
    }

    bool XmlValue::isTag() const
    {
        return m_type == XmlType::Tag;
    }

    XmlTag XmlValue::getTag(const XmlTag &def) const
    {
        if (m_type != XmlType::Tag)
            return def;
        return *m_tag;
    }

    void XmlValue::setTag(const XmlTag &value)
    {
        if (m_type == XmlType::Tag)
            *m_tag = value;
        else
        {
            drop();
            m_type = XmlType::Tag;
            m_tag = new XmlTag(value);
        }
    }

    XmlValue::operator XmlTag() const
    {
        return getTag();
    }

    const XmlTag &XmlValue::asTag() const
    {
        if (m_type != XmlType::Tag)
            return EmptyTag;
        return *m_tag;
    }

    XmlTag &XmlValue::asTag()
    {
        if (m_type != XmlType::Tag)
            throw std::runtime_error("Xml is not a tag value");
        return *m_tag;
    }

    const XmlString &XmlValue::getName() const
    {
        if (m_type != XmlType::Tag)
            return EmptyTag.name;
        return m_tag->name;
    }

    void XmlValue::setName(const XmlString &value)
    {
        if (m_type != XmlType::Tag)
            throw std::runtime_error("Xml is not a tag value");
        m_tag->name = value;
    }

    XmlString XmlValue::getAttribute(const XmlString &name, const XmlString &def) const
    {
        if (m_type != XmlType::Tag)
            return def;
        for (auto &pair : m_tag->attributes)
            if (pair.first == name)
                return pair.second;
        return def;
    }

    const XmlString &XmlValue::operator[](const XmlString &key) const
    {
        if (m_type != XmlType::Tag)
            return EmptyTag.name;
        for (auto &pair : m_tag->attributes)
            if (pair.first == key)
                return pair.second;
        return EmptyTag.name;
    }

    XmlString &XmlValue::operator[](const XmlString &key)
    {
        if (m_type != XmlType::Tag)
            throw std::runtime_error("Xml is not a tag value");
        return m_tag->attributes[key];
    }

    const XmlValue &XmlValue::operator[](szt index) const
    {
        if (m_type != XmlType::Tag)
            return Empty;
        if (index >= m_tag->content.size())
            return Empty;
        return m_tag->content.at(index);
    }

    void XmlValue::append(const XmlValue &value)
    {
        if (m_type != XmlType::Tag)
            throw std::runtime_error("Xml is not a tag value");
        m_tag->content.push_back(value);
    }

    void XmlValue::resize(szt count)
    {
        if (m_type != XmlType::Tag)
            throw std::runtime_error("Xml is not a tag value");
        m_tag->content.resize(count);
    }

    XmlValue &XmlValue::operator[](szt index)
    {
        if (m_type != XmlType::Tag)
            throw std::runtime_error("Xml is not a tag value");
        return m_tag->content[index];
    }

    void XmlValue::print(Printer &printer) const
    {
        XmlPrinter xprinter{printer};
        xprinter.printXml(*this);
    }

    bool XmlValue::scan(Scanner &scanner)
    {
        XmlScanner xscanner{scanner};
        auto success = xscanner.scanXml(*this);
        return success;
    }

    XmlValue::XmlValue(std::nullptr_t)
        : m_type(XmlType::Empty),
          m_text(nullptr)
    {
    }

    XmlValue::XmlValue(const XmlText &text)
        : m_type(XmlType::Text),
          m_text(new XmlText(text))
    {
    }

    XmlValue::XmlValue(const s8t &text)
        : m_type(XmlType::Text),
          m_text(new XmlText(text))
    {
    }

    XmlValue::XmlValue(const XmlString &name, const XmlAttributes &attributes, const XmlContent &content)
        : m_type(XmlType::Tag),
          m_tag(new XmlTag())
    {
        m_tag->name = name;
        m_tag->attributes = attributes;
        m_tag->content = content;
    }

    XmlValue::XmlValue(const XmlString &name, std::initializer_list<std::pair<const XmlString, XmlString>> attributes, std::initializer_list<XmlValue> content)
        : m_type(XmlType::Tag),
          m_tag(new XmlTag())
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
        : m_type(other.m_type)
    {
        switch (m_type)
        {
        case XmlType::Empty:
            m_text = nullptr;
            break;
        case XmlType::Text:
            m_text = new XmlText(*other.m_text);
            break;
        case XmlType::Tag:
            m_tag = new XmlTag();
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
        : XmlValue(nullptr)
    {
        *this = std::move(other);
    }

    XmlValue &XmlValue::operator=(XmlValue &&other)
    {
        drop();
        m_type = other.m_type;
        switch (m_type)
        {
        case XmlType::Empty:
            m_text = nullptr;
            break;
        case XmlType::Text:
            m_text = other.m_text;
            break;
        case XmlType::Tag:
            m_tag = other.m_tag;
            break;
        }
        other.m_type = XmlType::Empty;
        other.m_text = nullptr;
        return *this;
    }

    bool XmlValue::operator==(const XmlValue &other) const
    {
        if (m_type == other.m_type)
        {
            switch (m_type)
            {
            case XmlType::Empty:
                return true;
            case XmlType::Text:
                return *m_text == *other.m_text;
            case XmlType::Tag:
                return m_tag->name == other.m_tag->name && m_tag->attributes == other.m_tag->attributes && m_tag->content == other.m_tag->content;
            }
        }
        return false;
    }

    bool XmlValue::operator!=(const XmlValue &other) const
    {
        return !(*this == other);
    }

    XmlValue XmlValue::operator|(const XmlValue &other) const
    {
        XmlValue clone{*this};
        clone |= other;
        return std::move(clone);
    }

    XmlValue &XmlValue::operator|=(const XmlValue &other)
    {
        if (isEmpty())
            *this = other;
        else if (isTag() && other.isTag())
        {
            for (auto &pair : other.m_tag->attributes)
                m_tag->attributes.insert({pair.first, pair.second});
            for (szt i = 0; i < m_tag->content.size() && i < other.m_tag->content.size(); i++)
                m_tag->content.at(i) |= other.m_tag->content.at(i);
            while (m_tag->content.size() < other.m_tag->content.size())
                m_tag->content.push_back(other.m_tag->content.at(m_tag->content.size()));
        }
        return *this;
    }

    const XmlValue XmlValue::Empty = nullptr;
    const XmlText XmlValue::EmptyText{};
    const XmlTag XmlValue::EmptyTag{};

    void XmlValue::drop()
    {
        switch (m_type)
        {
        case XmlType::Text:
            delete m_text;
            break;
        case XmlType::Tag:
            delete m_tag;
            break;
        default:
            break;
        }
        m_type = XmlType::Empty;
        m_text = nullptr;
    }

}