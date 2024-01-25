#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <Cacto/Lang/Export.hpp>

namespace cacto
{

    class Scanner;
    class XmlValue;

    class CACTO_LANG_API XmlScanner
    {

    public:
        Scanner &getScanner() const;
        void setScanner(Scanner &value);

        bool scanText(std::string &text);
        bool scanTag(std::string &name, std::unordered_map<std::string, std::string> &attributes, std::vector<XmlValue> &content);
        bool scanXml(XmlValue &xml);

        XmlScanner(Scanner &scanner);
        virtual ~XmlScanner();

    private:
        Scanner *m_scanner;
    };

}
