#include <Cacto/Lang/Utils.hpp>
#include <Cacto/Lang/XmlPrinter.hpp>

namespace cacto
{

    void XmlPrinter::printText(const std::string &text)
    {
        std::string string = text;
        replaceAll(string, "&", "&amp;");
        replaceAll(string, "<", "&lt;");
        replaceAll(string, ">", "&gt;");
        replaceAll(string, "\"", "&quot;");
        replaceAll(string, "\'", "&pos;");
        print(string);
    }

    void XmlPrinter::printName(const std::string &name)
    {
        print(name);
    }

    void XmlPrinter::printAttribute(const std::string &attribute)
    {
        print(attribute);
    }

    void XmlPrinter::printValue(const std::string &value)
    {
        print('"' + value + '"');
    }

    XmlPrinter::XmlPrinter() = default;
    XmlPrinter::~XmlPrinter() = default;

}