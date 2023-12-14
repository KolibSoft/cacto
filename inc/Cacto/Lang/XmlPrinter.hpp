#pragma once

#include <Cacto/Lang/Printer.hpp>

namespace cacto
{

    class CACTO_LANG_API XmlPrinter
        : public Printer
    {

    public:
        void printText(const std::string &text);
        void printName(const std::string &name);
        void printAttribute(const std::string &attribute);
        void printValue(const std::string &value);

        XmlPrinter(std::ostream &stream);
        virtual ~XmlPrinter();
    };

}
