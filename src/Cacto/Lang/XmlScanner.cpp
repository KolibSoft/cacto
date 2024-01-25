#include <stdexcept>
#include <Cacto/Lang/Scanner.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Lang/StringUtils.hpp>
#include <Cacto/Lang/XmlScanner.hpp>

namespace cacto
{

    Scanner &XmlScanner::getScanner() const
    {
        return *m_scanner;
    }

    void XmlScanner::setScanner(Scanner &value)
    {
        m_scanner = &value;
    }

    bool XmlScanner::scanText(std::string &text)
    {
        auto scanEscape = [&]()
        {
            auto cursor = m_scanner->getCursor();
            if (m_scanner->scanToken("&") && (m_scanner->scanToken("lt") || m_scanner->scanToken("gt") || m_scanner->scanToken("amp") || m_scanner->scanToken("quot") || m_scanner->scanToken("pos")) && m_scanner->scanToken(";"))
                return true;
            m_scanner->setCursor(cursor);
            return false;
        };

        auto cursor = m_scanner->getCursor();
        while (scanEscape() || m_scanner->scanNotClass("&<>\"'\n"))
            continue;
        if (m_scanner->getCursor() > cursor)
        {
            auto token = m_scanner->take();
            text = token;
            replace(text, "&lt;", "<");
            replace(text, "&gt;", ">");
            replace(text, "&quot;", "\"");
            replace(text, "&pos;", "\'");
            replace(text, "&amp;", "&");
            return true;
        }
        return false;
    }

    bool XmlScanner::scanTag(std::string &name, std::unordered_map<std::string, std::string> &attributes, std::vector<XmlValue> &content)
    {
        auto scanIdentifier = [&](std::string &identifier)
        {
            auto cursor = m_scanner->getCursor();
            if (m_scanner->scanClass("_") || m_scanner->scanWord())
            {
                while (m_scanner->scanClass("_") || m_scanner->scanWord() || m_scanner->scanDigit() || m_scanner->scanClass(":-."))
                    continue;
                m_scanner->discardClass(":-.");
                if (m_scanner->getCursor() > cursor)
                {
                    auto token = m_scanner->take();
                    identifier = token;
                    return true;
                }
            }
            m_scanner->setCursor(cursor);
            return false;
        };

        auto scanEscape = [&]()
        {
            auto cursor = m_scanner->getCursor();
            if (m_scanner->scanToken("&") && (m_scanner->scanToken("lt") || m_scanner->scanToken("gt") || m_scanner->scanToken("amp") || m_scanner->scanToken("quot") || m_scanner->scanToken("pos")) && m_scanner->scanToken(";"))
                return true;
            m_scanner->setCursor(cursor);
            return false;
        };

        auto scanText = [&]()
        {
            auto cursor = m_scanner->getCursor();
            while (scanEscape() || m_scanner->scanNotClass("&<>\"'\n"))
                continue;
            return m_scanner->getCursor() > cursor;
        };

        auto scanValue = [&](std::string &value)
        {
            auto cursor = m_scanner->getCursor();
            if (m_scanner->scanToken("\"\"") || m_scanner->scanClass("\"") && scanText() && m_scanner->scanClass("\""))
            {
                auto token = m_scanner->take();
                value = token.substr(1, token.size() - 2);
                return true;
            }
            m_scanner->setCursor(cursor);
            return false;
        };

        if (m_scanner->dropToken("<"))
        {
            m_scanner->dropBlankln();
            if (!scanIdentifier(name))
                throw std::runtime_error("Expected tag name");
            m_scanner->dropBlankln();
            if (m_scanner->dropToken("/>"))
            {
                attributes.clear();
                content.clear();
                return true;
            }
            if (!m_scanner->dropToken(">"))
            {
                attributes.clear();
            attribute_item:
                m_scanner->dropBlankln();
                std::string aname{};
                if (!scanIdentifier(aname))
                    throw std::runtime_error("Expected attribute name");
                m_scanner->dropBlankln();
                if (!m_scanner->dropToken("="))
                    throw std::runtime_error("Expected '='");
                m_scanner->dropBlankln();
                std::string value{};
                if (!scanValue(value))
                    throw std::runtime_error("Expected attribute value");
                attributes[aname] = value;
                m_scanner->dropBlankln();
                if (m_scanner->dropToken("/>"))
                {
                    content.clear();
                    return true;
                }
                if (!m_scanner->dropToken(">"))
                    goto attribute_item;
            }
            m_scanner->dropBlankln();
            if (!m_scanner->dropToken("</"))
            {
                content.clear();
            content_item:
                content.push_back(nullptr);
                scanXml(content.back());
                m_scanner->dropBlankln();
                if (!m_scanner->dropToken("</"))
                    goto content_item;
            }
            m_scanner->dropBlankln();
            if (!m_scanner->dropToken(name))
                throw std::runtime_error("Unclosed xml tag");
            m_scanner->dropBlankln();
            if (!m_scanner->dropToken(">"))
                throw std::runtime_error("Expected '>'");
            return true;
        }
        return false;
    }

    bool XmlScanner::scanXml(XmlValue &xml)
    {
        std::string text{};
        if (scanText(text))
        {
            xml = text;
            return true;
        }

        std::string name{};
        std::unordered_map<std::string, std::string> attributes{};
        std::vector<XmlValue> content{};
        if (scanTag(name, attributes, content))
        {
            xml = {name, attributes, content};
            return true;
        }

        return false;
    }

    XmlScanner::XmlScanner(Scanner &scanner)
        : m_scanner(&scanner)
    {
    }

    XmlScanner::~XmlScanner() = default;

}