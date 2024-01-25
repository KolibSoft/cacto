#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class Printer;
    class XmlValue;

    class CACTO_LANG_API XmlPrinter
    {

    public:
        Printer &getPrinter() const;
        void setPrinter(Printer &value);

        void printText(const std::string &text);
        void printTag(const std::string &name, const std::unordered_map<std::string, std::string> &attributes, const std::vector<XmlValue> &content);
        void printXml(const XmlValue &xml);

        XmlPrinter(Printer &printer);
        virtual ~XmlPrinter();

    private:
        Printer *m_printer;
    };

}
