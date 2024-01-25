#include <Cacto/Lang/Printer.hpp>
#include <Cacto/Lang/XmlValue.hpp>
#include <Cacto/Lang/StringUtils.hpp>
#include <Cacto/Lang/XmlPrinter.hpp>

namespace cacto
{

    Printer &XmlPrinter::getPrinter() const
    {
        return *m_printer;
    }

    void XmlPrinter::setPrinter(Printer &value)
    {
        m_printer = &value;
    }

    void XmlPrinter::printText(const std::string &text)
    {
        std::string string = text;
        replace(string, "&", "&amp;");
        replace(string, "<", "&lt;");
        replace(string, ">", "&gt;");
        replace(string, "\"", "&quot;");
        replace(string, "\'", "&pos;");
        m_printer->print(string);
    }

    void XmlPrinter::printTag(const std::string &name, const std::unordered_map<std::string, std::string> &attributes, const std::vector<XmlValue> &content)
    {
        m_printer->print("<");
        m_printer->print(name);
        if (attributes.size() > 0)
        {
            auto it = attributes.begin();
            for (auto &value : attributes)
            {
                m_printer->print(" ");
                m_printer->print(value.first);
                m_printer->print("=");
                m_printer->print("\"");
                printText(value.second);
                m_printer->print("\"");
            }
        }
        if (content.size() > 0)
        {
            m_printer->print(">");
            for (auto &value : content)
            {
                printXml(value);
            }
            m_printer->print("</");
            m_printer->print(name);
            m_printer->print(">");
        }
        else
        {
            m_printer->print("/>");
        }
    }

    void XmlPrinter::printXml(const XmlValue &xml)
    {
        switch (xml.getKind())
        {
        case XmlValue::None:
            break;
        case XmlValue::Text:
            printText(xml.asText());
            break;
        case XmlValue::Tag:
            printTag(xml.getName(), xml.asAttributes(), xml.asContent());
            break;
        }
    }

    XmlPrinter::XmlPrinter(Printer &printer)
        : m_printer(&printer)
    {
    }

    XmlPrinter::~XmlPrinter() = default;

}