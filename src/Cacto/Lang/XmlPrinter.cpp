#include <Cacto/Lang/XmlPrinter.hpp>

namespace cacto
{

    void XmlPrinter::printText(const std::string &text)
    {
        print(text);
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