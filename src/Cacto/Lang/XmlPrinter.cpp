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

    void XmlPrinter::printAttribute(const std::string &attribute, const std::string &value)
    {
        print(attribute + "=\"" + value + '"');
    }

    XmlPrinter::XmlPrinter() = default;
    XmlPrinter::~XmlPrinter() = default;

}